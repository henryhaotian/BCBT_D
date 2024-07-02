#include "vrep_utilities.h"
#include <chrono>
#include <thread>
#include <complex>
#include <mutex>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" {
    #include "extApi.h"
   // #include "extApiCustom.h" // if you wanna use custom remote API functions!
}

simxInt clientID, mode = simx_opmode_oneshot_wait;

std::string Pick_Signal;
std::string Pick_Value = " ";

std::string Place_Signal;
std::string Place_Value = " ";

std::string ClearPathTo_Signal;
std::string ClearPathTo_Value = " ";

std::string DropObject_Signal;
std::string DropObject_Value = " ";

//other methos
std::string ClearPathTo_Signal_BTE;
std::string ClearPathTo_Value_BTE = " ";
std::string ClearPathTo_Signal_Base;
std::string ClearPathTo_Value_Base = " ";

namespace vrep_utilities
{

    void startSimulation()
    {
       simxStartSimulation(clientID, 0);
    }
    void stopSimulation()
    {
        simxStopSimulation(clientID, 0);
    }

    void init()
    {
        clientID = simxStart((simxChar*)"127.0.0.1",19997,true,false,2000,5);

        Pick_Signal = "pick_signal";
        Place_Signal = "place_signal";
        ClearPathTo_Signal = "clearpathto_signal";
        DropObject_Signal = "dropobject_signal";

        simxSetStringSignal(clientID, Pick_Signal.c_str(), (simxUChar*)Pick_Value.c_str(), Pick_Value.size(), mode);
        simxSetStringSignal(clientID, Place_Signal.c_str(), (simxUChar*)Place_Value.c_str(), Place_Value.size(), mode);
        simxSetStringSignal(clientID, ClearPathTo_Signal.c_str(), (simxUChar*)ClearPathTo_Value.c_str(), ClearPathTo_Value.size(), mode);
        simxSetStringSignal(clientID, DropObject_Signal.c_str(), (simxUChar*)DropObject_Value.c_str(), DropObject_Value.size(), mode);

        //other methods
        ClearPathTo_Signal_BTE = "clearpathto_signal_BTE";
        ClearPathTo_Signal_Base = "clearpathto_signal_Base";
        simxSetStringSignal(clientID, ClearPathTo_Signal_BTE.c_str(), (simxUChar*)ClearPathTo_Value_BTE.c_str(), ClearPathTo_Value_BTE.size(), mode);
        simxSetStringSignal(clientID, ClearPathTo_Signal_Base.c_str(), (simxUChar*)ClearPathTo_Value_Base.c_str(), ClearPathTo_Value_Base.size(), mode);
    }

    std::string GetCurrentObstacle(std::string name)
    {
        int input_string_num = 1;
        int output_string_num;
        const char* input_string = name.c_str();
        char* output_string;
        int result=simxCallScriptFunction(clientID,"UR5",sim_scripttype_childscript,"GetObstacle",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
        NULL,NULL,NULL,NULL,&output_string_num,&output_string,NULL,NULL,simx_opmode_blocking);
        return output_string;
    }

    void Pick(std::string name)
    {
        Pick_Value = name;
        simxSetStringSignal(clientID, Pick_Signal.c_str(), (simxUChar*)Pick_Value.c_str(), Pick_Value.size(), mode);
    }

    bool IsObjectOnHand(std::string name)
    {
        int input_string_num = 1;
        int output_string_num;
        const char* input_string = name.c_str();
        char* output_string;
        int result=simxCallScriptFunction(clientID,"UR5",sim_scripttype_childscript,"IsObjectOnHand",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
        NULL,NULL,NULL,NULL,&output_string_num,&output_string,NULL,NULL,simx_opmode_blocking);
        std::string res = output_string;
        if (res == "true")
        {
            return true;
        }
        else if (res == "false")
        {
            return false;
        }
    }
    
    bool IsHandEmpty()
    {
        int output_string_num;
        char* output_string;
        simxCallScriptFunction(clientID,"UR5",sim_scripttype_childscript,"IsHandEmpty",0,NULL,0,NULL,0,NULL,0,NULL,
        NULL,NULL,NULL,NULL,&output_string_num,&output_string,NULL,NULL,simx_opmode_blocking);
        std::string res = output_string;
        if (res == "true")
        {
            return true;
        }
        else if (res == "false")
        {
            return false;
        }
    }

    bool IsFreeToObject(std::string name)
    {
        int input_string_num = 1;
        int output_string_num;
        const char* input_string = name.c_str();
        char* output_string;
        int result=simxCallScriptFunction(clientID,"UR5",sim_scripttype_childscript,"IsFreeToObject",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
        NULL,NULL,NULL,NULL,&output_string_num,&output_string,NULL,NULL,simx_opmode_blocking);
        std::string res = output_string;
        if (res == "true")
        {
            return true;
        }
        else if (res == "false")
        {
            return false;
        }
    }

    bool IsFreeToGoal(std::string name)
    {
        int input_string_num = 1;
        int output_string_num;
        const char* input_string = name.c_str();
        char* output_string;
        int result=simxCallScriptFunction(clientID,"UR5",sim_scripttype_childscript,"IsFreeToGoal",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
        NULL,NULL,NULL,NULL,&output_string_num,&output_string,NULL,NULL,simx_opmode_blocking);
        std::string res = output_string;
        if (res == "true")
        {
            return true;
        }
        else if (res == "false")
        {
            return false;
        }
    }

    void Place(std::string name, std::string goal)
    {
        Place_Value = goal;
        simxSetStringSignal(clientID, Place_Signal.c_str(), (simxUChar*)Place_Value.c_str(), Place_Value.size(), mode);
    }

    bool IsObjectOnGoal(std::string name, std::string goal)
    {
        int input_string_num = 2;
        int output_string_num;
        const char* input_string;
        char* output_string;
        std::string a = '\0' + goal;
        std::string b = name+a;
        input_string = b.c_str();
        int result=simxCallScriptFunction(clientID,"UR5",sim_scripttype_childscript,"IsObjectOnGoal",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
        NULL,NULL,NULL,NULL,&output_string_num,&output_string,NULL,NULL,simx_opmode_blocking);
        std::string res = output_string;
        if (res == "true")
        {
            return true;
        }
        else if (res == "false")
        {
            return false;
        }
    }

    void ClearPathTo(std::string name)
    {
        ClearPathTo_Value = name;
        simxSetStringSignal(clientID, ClearPathTo_Signal.c_str(), (simxUChar*)ClearPathTo_Value.c_str(), ClearPathTo_Value.size(), mode);
    }

    void DropObject(std::string name)
    {
        DropObject_Value = name;
        simxSetStringSignal(clientID, DropObject_Signal.c_str(), (simxUChar*)DropObject_Value.c_str(), DropObject_Value.size(), mode);
    }
}
