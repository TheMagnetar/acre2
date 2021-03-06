#include "compat.h"

#include "TS3Client.h"
#include "Engine.h"
#include "Types.h"
#include "TsFunctions.h"
#include "shlobj.h"
#include "Shlwapi.h"
#include "Log.h"
#include <thread>
#include <exception>
#include <sstream>
#include <string>
#include <vector>

#include "AcreSettings.h"

#pragma comment(lib, "Shlwapi.lib")

#define INVALID_TS3_CHANNEL -1
#define DEFAULT_TS3_CHANNEL "ACRE"

extern TS3Functions ts3Functions;
typedef std::vector<std::string> Sentence;

//TS3Functions CTS3Client::ts3Functions;

ACRE_RESULT CTS3Client::initialize(void) {
    setPreviousTSChannel(INVALID_TS3_CHANNEL);
    return ACRE_OK;
}

ACRE_RESULT CTS3Client::setMuted(ACRE_ID id, BOOL muted) {
    anyID clientArray[2];
    
    clientArray[0] = (anyID)id;
    clientArray[1] = 0x0000;

    TRACE("MUTE: %d, %d", id, muted);

    if (muted) { 
        ts3Functions.requestMuteClients(ts3Functions.getCurrentServerConnectionHandlerID(), clientArray, NULL);
    } else {
        ts3Functions.requestUnmuteClients(ts3Functions.getCurrentServerConnectionHandlerID(), clientArray, NULL);
    }
    return ACRE_OK;
}

ACRE_RESULT CTS3Client::setMuted(std::list<ACRE_ID> idList, BOOL muted) {

    return ACRE_OK;
}

ACRE_RESULT CTS3Client::getMuted(ACRE_ID id) {

    return ACRE_OK;
}

ACRE_RESULT CTS3Client::stop() {
    if (CEngine::getInstance() != NULL) {
        CEngine::getInstance()->stop();
        this->setState(ACRE_STATE_STOPPING);
        if (this->m_versionThreadHandle.joinable()) {
            this->m_versionThreadHandle.join();
        }
        this->setState(ACRE_STATE_STOPPED);

    }
    return ACRE_OK;
}

ACRE_RESULT CTS3Client::start(ACRE_ID id) {
    CEngine::getInstance()->start(id);
    this->setInputActive(FALSE);
    this->setDirectFirst(FALSE);
    this->setMainPTTDown(FALSE);
    this->setRadioPTTDown(FALSE);
    this->setHitTSSpeakingEvent(FALSE);
    this->setOnRadio(FALSE);
    this->setState(ACRE_STATE_RUNNING);
    this->setIsX3DInitialized(FALSE);

    this->m_versionThreadHandle = std::thread(&CTS3Client::exPersistVersion, this);

    return ACRE_OK;
}

ACRE_RESULT CTS3Client::exPersistVersion( void ) {
    clock_t run, delta;
    
    ts3Functions.setClientSelfVariableAsString(ts3Functions.getCurrentServerConnectionHandlerID(), CLIENT_META_DATA, ACRE_VERSION_METADATA);
    ts3Functions.flushClientSelfUpdates(ts3Functions.getCurrentServerConnectionHandlerID(), NULL);
    
    ts3Functions.printMessageToCurrentTab("ACRE2 loaded and initialized");
    ts3Functions.printMessageToCurrentTab(ACRE_VERSION_METADATA);

    run = delta = clock() / CLOCKS_PER_SEC;
    while (this->getState() == ACRE_STATE_RUNNING && CEngine::getInstance()->getExternalServer()) {
        
        delta = (clock() / CLOCKS_PER_SEC) - run;
        if (delta > (PERSIST_VERSION_TIMER / 1000) ) {
            char selfVariableBuffer[4096];
            if (CEngine::getInstance()->getGameServer()->getConnected()) {
                _snprintf_s(selfVariableBuffer, 4094, "%s\nArma Connected: Yes", ACRE_VERSION_METADATA);
            } else {
                _snprintf_s(selfVariableBuffer, 4094, "%s\nArma Connected: No", ACRE_VERSION_METADATA);
            }
            ts3Functions.setClientSelfVariableAsString(ts3Functions.getCurrentServerConnectionHandlerID(), CLIENT_META_DATA, selfVariableBuffer);
            ts3Functions.flushClientSelfUpdates(ts3Functions.getCurrentServerConnectionHandlerID(), NULL);
            run = clock() / CLOCKS_PER_SEC;
        }

        Sleep(100);
    }

    return false;
}

BOOL CTS3Client::getVAD() {
    unsigned int res;
    char *data;
    BOOL returnValue = FALSE;
    res = ts3Functions.getPreProcessorConfigValue(ts3Functions.getCurrentServerConnectionHandlerID(), "vad", &data);
    if (!res) {
        if (!strcmp(data, "true")) {
            returnValue = TRUE;
        }
        ts3Functions.freeMemory(data);
    }
    return returnValue;
}

ACRE_RESULT CTS3Client::localStartSpeaking(ACRE_SPEAKING_TYPE speakingType) {
    this->localStartSpeaking(speakingType, "");
    return ACRE_OK;
}

ACRE_RESULT CTS3Client::localStartSpeaking(ACRE_SPEAKING_TYPE speakingType, std::string radioId) {
    BOOL stopDirectSpeaking = FALSE;
    

    if (speakingType == ACRE_SPEAKING_RADIO) {
        this->setRadioPTTDown(TRUE);
        this->setOnRadio(TRUE);
        if (!this->getVAD()) {
            if (!this->getDirectFirst()) {
                this->microphoneOpen(TRUE);
            }
            if (this->getDirectFirst()) {
                stopDirectSpeaking = TRUE;
            }
        } else {
            if (this->getTsSpeakingState() == STATUS_TALKING) {
                stopDirectSpeaking = TRUE;
            }
        }
    }
    if (stopDirectSpeaking) {
        CEngine::getInstance()->localStopSpeaking();
    }
    CEngine::getInstance()->localStartSpeaking(speakingType, radioId);
    return ACRE_OK;
}



ACRE_RESULT CTS3Client::localStopSpeaking(ACRE_SPEAKING_TYPE speakingType) {
    BOOL resendDirectSpeaking = FALSE;
    if (speakingType == ACRE_SPEAKING_RADIO || speakingType == ACRE_SPEAKING_UNKNOWN) {
        this->setRadioPTTDown(FALSE);
    }
    

    if (this->getOnRadio()) {
        if (!this->getVAD()) {
            if (speakingType == ACRE_SPEAKING_RADIO && this->getDirectFirst()) {
                this->setOnRadio(FALSE);
                resendDirectSpeaking = TRUE;
            } else {
                if (!((CTS3Client *)(CEngine::getInstance()->getClient()))->getMainPTTDown()) {
                    this->microphoneOpen(FALSE);
                } else {
                    resendDirectSpeaking = true;
                }
            }
        } else {
            this->setOnRadio(FALSE);
            if (this->getTsSpeakingState() == STATUS_TALKING) {
                resendDirectSpeaking = TRUE;
            }
        }
    }
    
    CEngine::getInstance()->localStopSpeaking();
    if (resendDirectSpeaking) {
        CEngine::getInstance()->localStartSpeaking(ACRE_SPEAKING_DIRECT);
    }
    
    return ACRE_OK;
}

ACRE_RESULT CTS3Client::enableMicrophone(BOOL status) {
    BOOL currentStatus = this->getInputStatus();
    unsigned int res;
    if (currentStatus != status) {
        if (status) {
            res = ts3Functions.setClientSelfVariableAsInt(ts3Functions.getCurrentServerConnectionHandlerID(), CLIENT_INPUT_MUTED, MUTEINPUT_NONE);
            if (res != ERROR_ok) {
                char* errorMsg;
                if (ts3Functions.getErrorMessage(res, &errorMsg) == ERROR_ok) {
                    LOG("Error toggling microphone enabled: %s\n", errorMsg);
                    ts3Functions.freeMemory(errorMsg);
                }
                return ACRE_OK;
            }
        } else {
            res = ts3Functions.setClientSelfVariableAsInt(ts3Functions.getCurrentServerConnectionHandlerID(), CLIENT_INPUT_MUTED, MUTEINPUT_MUTED);
            if (res != ERROR_ok) {
                char* errorMsg;
                if (ts3Functions.getErrorMessage(res, &errorMsg) == ERROR_ok) {
                    LOG("Error, failed to disable microphone input: %s\n", errorMsg);
                    ts3Functions.freeMemory(errorMsg);
                }
                return ACRE_OK;
            }
        }
        res = ts3Functions.flushClientSelfUpdates(ts3Functions.getCurrentServerConnectionHandlerID(), NULL);
        if (!(res == ERROR_ok || res == ERROR_ok_no_update)) {
            char* errorMsg;
            if (ts3Functions.getErrorMessage(res, &errorMsg) == ERROR_ok) {
                LOG("STOP TALKING: Error flushing after toggling microphone muted: %s\n", errorMsg);
                ts3Functions.freeMemory(errorMsg);
            }
            return ACRE_ERROR;
        }
    }
    return ACRE_OK;
}

BOOL CTS3Client::getInputStatus() {
    BOOL status;
    unsigned int res, ret;
    res = ts3Functions.getClientSelfVariableAsInt(ts3Functions.getCurrentServerConnectionHandlerID(), CLIENT_INPUT_MUTED, (int *)&ret);
    if (res != ERROR_ok) {
        char* errorMsg;
        if (ts3Functions.getErrorMessage(res, &errorMsg) == ERROR_ok) {
            LOG("Error querying microphone input status: %s\n", errorMsg);
            ts3Functions.freeMemory(errorMsg);
        }
        return FALSE;
    }

    if (ret == MUTEINPUT_NONE)
        status = TRUE;
    else 
        status = FALSE;

    return status;
}

ACRE_RESULT CTS3Client::playSound(std::string path, ACRE_VECTOR position, float volume, int looping) {
    unsigned long long playHandle;
    unsigned int ret, res;

    if (!PathFileExistsA(path.c_str()))
        return ACRE_ERROR;

    char soundpackDb[32];
    res = ts3Functions.getClientSelfVariableAsInt(ts3Functions.getCurrentServerConnectionHandlerID(), CLIENT_OUTPUT_MUTED, (int *)&ret);
    if (res != ERROR_ok) {
        char* errorMsg;
        if (ts3Functions.getErrorMessage(res, &errorMsg) == ERROR_ok) {
            LOG("Error checking playback status: %s\n", errorMsg);
            ts3Functions.freeMemory(errorMsg);
        }
        return ACRE_ERROR;
    }

    if (ret) {
        return ACRE_OK;
    }

    // create a volume ranged from -40 to 0dB change
    _snprintf_s(soundpackDb, 32, "%f", (-40.0f + (40.0f * volume) ) );
    // change the soundpack volume for this squawks volume
    ts3Functions.setPlaybackConfigValue(ts3Functions.getCurrentServerConnectionHandlerID(),
        "volume_factor_wave",
        soundpackDb);

    TS3_VECTOR vector = {position.x, position.z, position.y};

    TRACE("HIT [%f,%f,%f]", vector.x, vector.z, vector.y);
    ret = ts3Functions.playWaveFileHandle(ts3Functions.getCurrentServerConnectionHandlerID(),
        path.c_str(),
        looping,
        &playHandle);
    ret = ts3Functions.set3DWaveAttributes(ts3Functions.getCurrentServerConnectionHandlerID(),
        playHandle,
        &vector);
    return ACRE_OK;
}

std::string CTS3Client::getUniqueId( ) {
    char *uniqueId;
    std::string serverUniqueId = "";
    unsigned int res;

    res = ts3Functions.getServerVariableAsString(ts3Functions.getCurrentServerConnectionHandlerID(), VIRTUALSERVER_UNIQUE_IDENTIFIER, &uniqueId);
    if (res == ERROR_ok) {
        serverUniqueId = std::string(uniqueId);
        if (uniqueId) {
            ts3Functions.freeMemory(uniqueId);
        }
    }
    return serverUniqueId;
}

std::string CTS3Client::getConfigFilePath(void) {
    char tempPath[MAX_PATH-14];
    
    ts3Functions.getConfigPath(tempPath, MAX_PATH-14);

    std::string tempFolder = std::string(tempPath);
    tempFolder += "\\acre";
    if (!PathFileExistsA(tempFolder.c_str())) {
        if (!CreateDirectoryA(tempFolder.c_str(), NULL)) {
            LOG("ERROR: UNABLE TO CREATE TEMP DIR");
        }
    }

    return tempFolder;
}

std::string CTS3Client::getTempFilePath( void ) {
    char tempPath[MAX_PATH-14];
    GetTempPathA(sizeof(tempPath), tempPath);
    std::string tempFolder = std::string(tempPath);
    tempFolder += "\\acre";
    if (!PathFileExistsA(tempFolder.c_str())) {
        if (!CreateDirectoryA(tempFolder.c_str(), NULL)) {
            LOG("ERROR: UNABLE TO CREATE TEMP DIR");
        }
    }

    return tempFolder;
}

ACRE_RESULT CTS3Client::microphoneOpen(BOOL status) {
    unsigned int res;
    int micStatus;
    if (status) {
        micStatus = INPUT_ACTIVE;
        this->setInputActive(TRUE);
    } else {
        micStatus = INPUT_DEACTIVATED;
        this->setInputActive(FALSE);
    }
    res = ts3Functions.setClientSelfVariableAsInt(ts3Functions.getCurrentServerConnectionHandlerID(), CLIENT_INPUT_DEACTIVATED, micStatus);
    if (res != ERROR_ok) {
        char* errorMsg;
        if (ts3Functions.getErrorMessage(res, &errorMsg) == ERROR_ok) {
            LOG("STOP TALKING: Error toggling push-to-talk: %s\n", errorMsg);
            ts3Functions.freeMemory(errorMsg);
        }
        return ACRE_ERROR;
    }
        
    res = ts3Functions.flushClientSelfUpdates(ts3Functions.getCurrentServerConnectionHandlerID(), NULL);
    if (!(res == ERROR_ok || res == ERROR_ok_no_update)) {
        char* errorMsg;
        if (ts3Functions.getErrorMessage(res, &errorMsg) == ERROR_ok) {
            LOG("STOP TALKING: Error flushing after toggling push-to-talk: %s\n", errorMsg);
            ts3Functions.freeMemory(errorMsg);
        }
        return ACRE_ERROR;
    }
    return ACRE_OK;
}

ACRE_RESULT CTS3Client::unMuteAll( void ) {
    anyID clientId;
    anyID *clientList;
    unsigned int res;
    uint32_t total_retries = 0;
    uint32_t total_intentional_runs = 0;

    //for (total_intentional_runs = 0; total_intentional_runs < 3; total_intentional_runs++) {
        res = ts3Functions.getClientID(ts3Functions.getCurrentServerConnectionHandlerID(), &clientId);
        if (res == ERROR_ok) {

            res = ERROR_undefined;
            for (total_retries = 0; total_retries < 5 && res != ERROR_ok; total_retries++) {
                res = ts3Functions.getClientList(ts3Functions.getCurrentServerConnectionHandlerID(), &clientList);
                if (res == ERROR_ok) {
                    res = ts3Functions.requestUnmuteClients(ts3Functions.getCurrentServerConnectionHandlerID(), clientList, NULL);
                    //if (res != ERROR_ok) {
                    //    Sleep(500 * total_retries);
                    //}
                    ts3Functions.freeMemory(clientList);
                }
            }
            
            /*
            /*    - This was the alternative method originally, but it was hitting the spam threshold */
            /* Disable this method
            res = ts3Functions.getClientList(ts3Functions.getCurrentServerConnectionHandlerID(), &clientList);
            if (res == ERROR_ok) {
                for (x=0;clientList[x]!=0 && total_retries < 20;x++) {
                    anyID tempList[2];
                    uint32_t tries_on_client;

                    tempList[0] = (anyID)clientList[x];
                    tempList[1] = 0x0000;

                    res = ts3Functions.requestUnmuteClients(ts3Functions.getCurrentServerConnectionHandlerID(), clientList, NULL);
                    for (tries_on_client = 0; tries_on_client < 5 && total_retries < 20 && res != ERROR_ok; tries_on_client++, total_retries++) {
                            res = ts3Functions.requestUnmuteClients(ts3Functions.getCurrentServerConnectionHandlerID(), tempList, NULL);
                            if (res != ERROR_ok) {
                                Sleep(500 * tries_on_client);
                            }
                    }
                }
                ts3Functions.freeMemory(clientList);
            }
            */
        }
    //    Sleep(500);
    //}
    return ACRE_OK;
}

ACRE_RESULT CTS3Client::moveToServerTS3Channel() {
    //Only switch channel if enabled in settings
    if (!CAcreSettings::getInstance()->getDisableTS3ChannelSwitch()) {
        anyID clientId;
        std::string serverName = getServerName();

        if (ts3Functions.getClientID(ts3Functions.getCurrentServerConnectionHandlerID(), &clientId) == ERROR_ok) {
            uint64 channelId = INVALID_TS3_CHANNEL;
            uint64 currentChannelId = INVALID_TS3_CHANNEL;
            //Get current channel and store
            if (ts3Functions.getChannelOfClient(ts3Functions.getCurrentServerConnectionHandlerID(), clientId, &currentChannelId) == ERROR_ok && getPreviousTSChannel() == INVALID_TS3_CHANNEL) {
                //LOG("Storing current channel: %d", currentChannelId);
                setPreviousTSChannel(currentChannelId);
            } else {
                //LOG("Can't get current channel or is the same channel");
            }

            channelId = findChannelByName(serverName);
            if (channelId != INVALID_TS3_CHANNEL) {
                //LOG("Trying to move to channel: %d", channelId);
                if (channelId != INVALID_TS3_CHANNEL && channelId != currentChannelId) {
                    if (ts3Functions.requestClientMove(ts3Functions.getCurrentServerConnectionHandlerID(), clientId, channelId, "", NULL) == ERROR_ok) {
                        //LOG("Moved to channel: %d", channelId);
                    } else {
                        //LOG("Couldn't move to channel: %d", channelId);
                    }
                }
            } else {
                //LOG("Couldn't find channel contianing %s or a default channel", serverName);
            }
        }
    }
    setShouldSwitchTS3Channel(false);
    return ACRE_OK;
}

ACRE_RESULT CTS3Client::moveToPreviousTS3Channel() {
    if (!CAcreSettings::getInstance()->getDisableTS3ChannelSwitch()) {
        anyID clientId;
        if (ts3Functions.getClientID(ts3Functions.getCurrentServerConnectionHandlerID(), &clientId) == ERROR_ok) {
            uint64 channelId = INVALID_TS3_CHANNEL;
            uint64 currentChannelId = INVALID_TS3_CHANNEL;
            if (ts3Functions.getChannelOfClient(ts3Functions.getCurrentServerConnectionHandlerID(), clientId, &currentChannelId) == ERROR_ok) {
                channelId = getPreviousTSChannel();
                if (channelId != INVALID_TS3_CHANNEL && channelId != currentChannelId) {
                    //LOG("Trying to move to original channel: %d", channelId);
                    if (ts3Functions.requestClientMove(ts3Functions.getCurrentServerConnectionHandlerID(), clientId, channelId, "", NULL) == ERROR_ok) {
                        //LOG("Moved to channel: %d", channelId);
                    } else {
                        //LOG("Couldn't move to channel: %d", channelId);
                    }
                } else {
                    //LOG("Same channel or no original channel to switch to");
                }
            } else {
                //LOG("Can't get current channel");
            }
        }
        setPreviousTSChannel(INVALID_TS3_CHANNEL);
    }
    return ACRE_OK;
}

uint64 CTS3Client::findChannelByName(std::string name) {
    uint64 *channelList;
    uint64 channelId = INVALID_TS3_CHANNEL;
    char* channelName;
    std::map<uint64, std::string> channelMap;
    int bestDistance = 40;
    uint64 bestChannelId = INVALID_TS3_CHANNEL;

    if (ts3Functions.getChannelList(ts3Functions.getCurrentServerConnectionHandlerID(), &channelList) == ERROR_ok) {
        while (*channelList) {
            channelId = *channelList;
            channelList++;
            //LOG("Found channel: %d", channelId);
            if (ts3Functions.getChannelVariableAsString(ts3Functions.getCurrentServerConnectionHandlerID(), channelId, CHANNEL_NAME, &channelName) == ERROR_ok) {
                std::string channelNameString = std::string(channelName);
                if (channelNameString.find(DEFAULT_TS3_CHANNEL) != -1) {
                    channelMap.emplace(channelId, channelNameString);
                }
            } else {
                //LOG("Can't get channel name");
            }
        }

        for (auto& element : channelMap) {
            int distance = levenshteinDistance(split(element.second, ' '), split(name, ' ')) + levenshteinDistance(split(name, ' '), split(element.second, ' '));
            //LOG("Combined istance between '%s' and '%s' is %d", element.second.c_str(), name.c_str(), distance);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestChannelId = element.first;
                //LOG("New best channel is '%s'", element.second.c_str());
            }
        }
        return bestChannelId;
    } else {
        //LOG("Can't get channel list");
    }
    return INVALID_TS3_CHANNEL;
}

unsigned int CTS3Client::levenshteinDistance(const Sentence& string1, const Sentence& string2) {
    const std::size_t len1 = string1.size(), len2 = string2.size();
    std::vector<unsigned int> col(len2 + 1), prevCol(len2 + 1);

    for (unsigned int i = 0; i < prevCol.size(); i++)
        prevCol[i] = i;
    for (unsigned int i = 0; i < len1; i++) {
        col[0] = i + 1;
        for (unsigned int j = 0; j < len2; j++)
            col[j + 1] = std::min({prevCol[1 + j] + 1, col[j] + 1, prevCol[j] + (string1[i] == string2[j] ? 0 : 1)});
        col.swap(prevCol);
    }
    return prevCol[len2];
}

Sentence CTS3Client::split(const std::string &s, char delim, Sentence &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

Sentence CTS3Client::split(const std::string &s, char delim) {
    Sentence elems;
    split(s, delim, elems);
    return elems;
}

ACRE_RESULT CTS3Client::updateServerName(std::string name) {
    setServerName(name);
    if (name != "") {
        updateShouldSwitchTS3Channel(true);
    }
    return ACRE_OK;
}

ACRE_RESULT CTS3Client::updateShouldSwitchTS3Channel(BOOL state) {
    setShouldSwitchTS3Channel(state);
    return ACRE_OK;
}

BOOL CTS3Client::shouldSwitchTS3Channel() {
    return getShouldSwitchTS3Channel();
}
