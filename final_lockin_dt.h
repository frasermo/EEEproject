/*
 * FRASER MONTANDON
 * LOCK-IN FIR FILTER
 * GENERATED WITH CCS2000 AND MATLAB SIMULINK
 */


#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(void*),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(codertarget_tic2000_blocks_DA_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "codertarget_tic2000_blocks_DA_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&final_lockin_B.ADCin), 0, 0, 11 }
  ,

  { (char_T *)(&final_lockin_DW.DigitalFilter_states[0]), 0, 0, 1326 },

  { (char_T *)(&final_lockin_DW.decimator_inphase_PhaseIdx), 6, 0, 2 },

  { (char_T *)(&final_lockin_DW.cosinusoid_TableIdx), 5, 0, 2 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  4U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&final_lockin_P.bias_Value), 0, 0, 1288 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  1U,
  rtPTransitions
};

/* [EOF] final_lockin_dt.h */
