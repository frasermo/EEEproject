/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: final_lockin_private.h
 *
 * Code generated for Simulink model 'final_lockin'.
 *
 * Model version                  : 1.99
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Sun Nov  7 18:46:23 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_final_lockin_private_h_
#define RTW_HEADER_final_lockin_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

void InitAdcA (void);
void config_ADCA_SOC0 (void);
extern uint16_T MW_adcAInitFlag;
extern real_T rt_roundd_snf(real_T u);

#endif                                 /* RTW_HEADER_final_lockin_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
