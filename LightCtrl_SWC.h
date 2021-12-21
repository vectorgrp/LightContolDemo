#ifndef RTW_HEADER_LightCtrl_SWC_h_
#define RTW_HEADER_LightCtrl_SWC_h_

typedef unsigned char uint8_T;
typedef unsigned short uint16_T;
typedef double real_T;

typedef struct tag_DW_LightCtrl_SWC_T
{
  real_T HysteresisTimer;
  uint8_T is_active_c1_LightCtrl_SWC;
  uint8_T is_c1_LightCtrl_SWC;
  uint8_T is_AutoMode;
} DW_LightCtrl_SWC_T;

struct P_LightCtrl_SWC_T_ 
{
  real_T LightIntensityToOff_Value;
  real_T LightIntensityToOn_Value;
  real_T HysteresisTimeToOff_Value;
  real_T HysteresisTimeToOn_Value;
  real_T CycleTime_Value;
};

typedef struct P_LightCtrl_SWC_T_ P_LightCtrl_SWC_T;

extern P_LightCtrl_SWC_T LightCtrl_SWC_P;
extern DW_LightCtrl_SWC_T LightCtrl_SWC_DW;

extern void LightCtrl(void);
extern void LightCtrl_Init(void);

#endif    // RTW_HEADER_LightCtrl_SWC_h_ 