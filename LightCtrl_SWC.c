/*
 * This file contains generated ccde for a model 'LightCtrl_SWC'.
 * It is an implementation of the light control ECU we want to test.
 */

#include <stdbool.h>
#include "IO.h"
#include "LightCtrl_SWC.h"

#define LightCtrl_SWC_IN_AutoMode      ((uint8_T)1U)
#define LightCtrl_SWC_IN_EnterAutoMode ((uint8_T)1U)
#define LightCtrl_SWC_IN_LightOff      ((uint8_T)2U)
#define LightCtrl_SWC_IN_LightOn       ((uint8_T)3U)
#define LightCtrl_SWC_IN_LightToOff    ((uint8_T)4U)
#define LightCtrl_SWC_IN_LightToOn     ((uint8_T)5U)
#define LightCtrl_SWC_IN_OffMode       ((uint8_T)2U)
#define LightCtrl_SWC_IN_OnMode        ((uint8_T)3U)
#define LightCtrl_SW_IN_NO_ACTIVE_CHILD ((uint8_T)0U)

const uint8_T C_LightCtrl_SWC_IN_AutoMode = LightCtrl_SWC_IN_AutoMode;
const uint8_T C_LightCtrl_SWC_IN_EnterAutoMode = LightCtrl_SWC_IN_EnterAutoMode;
const uint8_T C_LightCtrl_SWC_IN_LightOff = LightCtrl_SWC_IN_LightOff;
const uint8_T C_LightCtrl_SWC_IN_LightOn = LightCtrl_SWC_IN_LightOn;
const uint8_T C_LightCtrl_SWC_IN_LightToOff = LightCtrl_SWC_IN_LightToOff;
const uint8_T C_LightCtrl_SWC_IN_LightToOn = LightCtrl_SWC_IN_LightToOn;
const uint8_T C_LightCtrl_SWC_IN_OffMode = LightCtrl_SWC_IN_OffMode;
const uint8_T C_LightCtrl_SWC_IN_OnMode = LightCtrl_SWC_IN_OnMode;
const uint8_T C_LightCtrl_SW_IN_NO_ACTIVE_CHILD = LightCtrl_SW_IN_NO_ACTIVE_CHILD;

#define VARIANT_US
#define VARIANT_DE


DW_LightCtrl_SWC_T LightCtrl_SWC_DW;

P_LightCtrl_SWC_T LightCtrl_SWC_P = 
{
  70.0,        // LightIntensityToOff
  60.0,        // LightIntensityToOn
  3.0,         // HysteresisTimeToOff
  2.0,         // HysteresisTimeToOn
  0.01         // CycleTime
};


void Transition_S2_37(void)
{
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
}

void Transition_S2_39(void)
{
 #ifdef VARIANT_US 
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SW_IN_NO_ACTIVE_CHILD;
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OnMode;
 #else
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SW_IN_NO_ACTIVE_CHILD;
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OnMode; 
 #endif
 
}

void Transition_S2_41(void)
{
  #ifdef VARIANT_US == 1
	LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SW_IN_NO_ACTIVE_CHILD;
	LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
  #else VARIANT_US == 2
	LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SW_IN_NO_ACTIVE_CHILD;
	LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
  #endif
}

void Transition_S2_32(void)
{
	#ifdef VARIANT_DE == 1
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
	#elif VARIANT_DE == 2
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
	#else
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
	#endif
  
}

void Transition_S2_33(void)
{
	#ifdef VARIANT_DE == 2
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
	#else
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOn;
	#endif  
}

void Transition_S2_19(void)
{
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOn;
}

void Transition_S2_29(void)
{
  Output_HeadLight(false);
  LightCtrl_SWC_DW.HysteresisTimer = 0.0;
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
}

void Transition_S2_20(void)
{
	#ifdef VARIANT_DE == 1 &&  VARIANT_US == 1
		LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOff;
	#else
		LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOff;
	#endif
}

void Transition_S2_28(void)
{
  Output_HeadLight(true);
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOn;

  // We create a fault injection here. This function has now an "implementation error".
  // With this error in the code, 1 test case fails.
  // To see how VectorCAST's Change Based Testing feature works, "fix" the error in this function (see below).
  // Then, run the test cases in VectorCAST Manage again.
  // You will notice that multiple test cases will be executed: not only the failed one but also all those this function affects.
  // However, the unaffected test cases will not be executed at all.

  // Replace the value '3.0' in this line with '0.0' to fix the "implementation error".
  #ifdef VARIANT_US == 1
  LightCtrl_SWC_DW.HysteresisTimer = 3.0;
  #else
  LightCtrl_SWC_DW.HysteresisTimer = 0.0;
  #endif
	  
}

void Transition_S2_23(void)
{
	#ifdef VARIANT_US == 1
	 LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOn;
	#else
	 LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOn;
	#endif
}

void Transition_S2_6(void)
{
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
}

void Transition_S2_25(void)
{
  LightCtrl_SWC_DW.HysteresisTimer += LightCtrl_SWC_P.CycleTime_Value;
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOff;
}

void Transition_S2_22(void)
{
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
}

void Transition_S2_18(void)
{
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOn;
}

void Transition_S2_24(void)
{
  LightCtrl_SWC_DW.HysteresisTimer += LightCtrl_SWC_P.CycleTime_Value;
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOn;
}

void Transition_S2_38(void)
{
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_AutoMode;
}

void Transition_S2_31(void)
{
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_EnterAutoMode;
}

void Transition_S2_45(void)
{
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OnMode;
}

void Transition_S2_43(void)
{
  Output_HeadLight(false);
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
}

void Transition_S2_40(void)
{
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
}

void Transition_S2_42(void)
{
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_AutoMode;
}

void Transition_S2_44(void)
{
  Output_HeadLight(true);
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OnMode;
}

/* Model step function */
void LightCtrl(void)
{
  uint8_T Input_LightSwitch_local_storage;
  uint16_T rtb_LightIntensity_LightIntensi;

  Input_LightSwitch(&Input_LightSwitch_local_storage);
  Input_LightIntensity(&rtb_LightIntensity_LightIntensi);

  if (LightCtrl_SWC_DW.is_active_c1_LightCtrl_SWC == 0U)
  {
    LightCtrl_SWC_DW.is_active_c1_LightCtrl_SWC = 1U;
    Transition_S2_37();
  }
  else
  {
    switch (LightCtrl_SWC_DW.is_c1_LightCtrl_SWC)
    {
      case LightCtrl_SWC_IN_AutoMode:
        if (Input_LightSwitch_local_storage == 1)
        {
          Transition_S2_39();
        }
        else if (Input_LightSwitch_local_storage == 0)
        {
          Transition_S2_41();
        }
        else
        {
          switch (LightCtrl_SWC_DW.is_AutoMode)
          {
            case LightCtrl_SWC_IN_EnterAutoMode:
              if (rtb_LightIntensity_LightIntensi > LightCtrl_SWC_P.LightIntensityToOff_Value)
              {
                Transition_S2_32();
              }
              else
              {
                Transition_S2_33();
              }

              break;

            case LightCtrl_SWC_IN_LightOff:
              if (rtb_LightIntensity_LightIntensi < LightCtrl_SWC_P.LightIntensityToOn_Value)
              {
                Transition_S2_19();
              }
              else
              {
                Transition_S2_29();
              }

              break;

            case LightCtrl_SWC_IN_LightOn:
              if (rtb_LightIntensity_LightIntensi > LightCtrl_SWC_P.LightIntensityToOff_Value)
              {
                Transition_S2_20();
              }
              else
              {
                Transition_S2_28();
              }

              break;

            case LightCtrl_SWC_IN_LightToOff:
              if (rtb_LightIntensity_LightIntensi <= LightCtrl_SWC_P.LightIntensityToOff_Value)
              {
                Transition_S2_23();
              }
              else if (LightCtrl_SWC_DW.HysteresisTimer >= LightCtrl_SWC_P.HysteresisTimeToOff_Value)
              {
                Transition_S2_6();
              }
              else
              {
                Transition_S2_25();
              }

              break;

            default:
              if (rtb_LightIntensity_LightIntensi >= LightCtrl_SWC_P.LightIntensityToOn_Value)
              {
                Transition_S2_22();
              }
              else if (LightCtrl_SWC_DW.HysteresisTimer >= LightCtrl_SWC_P.HysteresisTimeToOn_Value)
              {
                Transition_S2_18();
              }
              else
              {
                Transition_S2_24();
              }

              break;
          }
        }

        break;

      case LightCtrl_SWC_IN_OffMode:
        if (Input_LightSwitch_local_storage == 2)
        {
          Transition_S2_38();
          Transition_S2_31();
        }
        else if (Input_LightSwitch_local_storage == 1)
        {
          Transition_S2_45();
        }
        else
        {
          Transition_S2_43();
        }

        break;

      default:
        if (Input_LightSwitch_local_storage == 0)
        {
          Transition_S2_40();
        }
        else if (Input_LightSwitch_local_storage == 2)
        {
          Transition_S2_42();
          Transition_S2_31();
        }
        else
        {
          Transition_S2_44();
        }

        break;
    }
  }
}

/* Model initialize function */
void LightCtrl_Init(void)
{
  Output_HeadLight(false);
}