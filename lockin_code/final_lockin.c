/*
 * FRASER MONTANDON
 * LOCK-IN FIR FILTER
 * GENERATED WITH CCS2000 AND MATLAB SIMULINK
 */


#include "final_lockin.h"
#include "final_lockin_private.h"
#include "final_lockin_dt.h"

/* Block signals (default storage) */
B_final_lockin_T final_lockin_B;

/* Block states (default storage) */
DW_final_lockin_T final_lockin_DW;

/* Real-time model */
static RT_MODEL_final_lockin_T final_lockin_M_;
RT_MODEL_final_lockin_T *const final_lockin_M = &final_lockin_M_;
static void rate_monotonic_scheduler(void);
uint16_T MW_adcAInitFlag = 0;

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to "remember" which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void final_lockin_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(final_lockin_M, 1));
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 0 shares data with slower tid rate: 1 */
  final_lockin_M->Timing.RateInteraction.TID0_1 =
    (final_lockin_M->Timing.TaskCounters.TID[1] == 0);

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (final_lockin_M->Timing.TaskCounters.TID[1])++;
  if ((final_lockin_M->Timing.TaskCounters.TID[1]) > 9) {/* Sample time: [0.000125s, 0.0s] */
    final_lockin_M->Timing.TaskCounters.TID[1] = 0;
  }
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function for TID0 */
void final_lockin_step0(void)          /* Sample time: [1.25E-5s, 0.0s] */
{
  real_T rtb_sinusoid;
  real_T zCurr;
  int32_T coeffIdx_tmp;
  int32_T decimator_inphase_Sums_tmp;
  int32_T tempAccChanOffset;
  int16_T iIdx;
  int16_T n;
  uint16_T tmp;

  {                                    /* Sample time: [1.25E-5s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* S-Function (sdspsine2): '<Root>/cosinusoid' */
  rtb_sinusoid = final_lockin_ConstP.cosinusoid_Values_SineTable[(int32_T)
    final_lockin_DW.cosinusoid_TableIdx];
  final_lockin_DW.cosinusoid_TableIdx++;
  if (final_lockin_DW.cosinusoid_TableIdx >= 80U) {
    final_lockin_DW.cosinusoid_TableIdx = 0U;
  }

  /* End of S-Function (sdspsine2): '<Root>/cosinusoid' */

  /* MATLABSystem: '<Root>/DACout' incorporates:
   *  Constant: '<Root>/bias'
   *  Sum: '<Root>/biasadjustment4'
   */
  zCurr = rt_roundd_snf(rtb_sinusoid + final_lockin_P.bias_Value);
  if (zCurr < 65536.0) {
    if (zCurr >= 0.0) {
      tmp = (uint16_T)zCurr;
    } else {
      tmp = 0U;
    }
  } else {
    tmp = MAX_uint16_T;
  }

  MW_C2000DAC(0U, tmp);

  /* End of MATLABSystem: '<Root>/DACout' */

  /* S-Function (c2802xadc): '<Root>/ADCin' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    AdcaRegs.ADCSOCFRC1.bit.SOC0 = 1;

    /* Wait for the period of Sampling window and EOC result to be latched after trigger */
    asm(" RPT #75 || NOP");
    final_lockin_B.ADCin = (AdcaResultRegs.ADCRESULT0);
  }

  /* Product: '<Root>/biasadjustment3' incorporates:
   *  Constant: '<Root>/bias'
   *  Sum: '<Root>/biasadjustment2'
   */
  final_lockin_B.biasadjustment3 = (final_lockin_B.ADCin -
    final_lockin_P.bias_Value) / final_lockin_P.bias_Value;

  /* DiscreteFir: '<S1>/Digital Filter' incorporates:
   *  Constant: '<Root>/bias'
   *  Product: '<Root>/biasadjustment'
   *  Product: '<Root>/inphase'
   */
  final_lockin_B.DigitalFilter = rtb_sinusoid / final_lockin_P.bias_Value *
    final_lockin_B.biasadjustment3;
  rtb_sinusoid = 0.0;

  /* load input sample */
  for (n = 0; n < 75; n++) {
    /* shift state */
    zCurr = final_lockin_B.DigitalFilter;
    final_lockin_B.DigitalFilter = final_lockin_DW.DigitalFilter_states[(int32_T)
      n];
    final_lockin_DW.DigitalFilter_states[(int32_T)n] = zCurr;

    /* compute one tap */
    rtb_sinusoid += final_lockin_P.DigitalFilter_Coefficients[(int32_T)n] *
      zCurr;
  }

  /* compute last tap */
  /* store output sample */
  final_lockin_B.DigitalFilter = final_lockin_P.DigitalFilter_Coefficients
    [(int32_T)n] * final_lockin_B.DigitalFilter + rtb_sinusoid;

  /* End of DiscreteFir: '<S1>/Digital Filter' */

  /* S-Function (sdspsine2): '<Root>/sinusoid' */
  rtb_sinusoid = final_lockin_ConstP.sinusoid_Values_SineTable[(int32_T)
    final_lockin_DW.sinusoid_TableIdx];
  final_lockin_DW.sinusoid_TableIdx++;
  if (final_lockin_DW.sinusoid_TableIdx >= 80U) {
    final_lockin_DW.sinusoid_TableIdx = 0U;
  }

  /* End of S-Function (sdspsine2): '<Root>/sinusoid' */

  /* S-Function (sdspfirdn2): '<Root>/decimator_inphase' */
  coeffIdx_tmp = (int32_T)(final_lockin_DW.decimator_inphase_PhaseIdx * 24LL);
  for (n = 0; n < 24; n++) {
    decimator_inphase_Sums_tmp = coeffIdx_tmp + n;
    final_lockin_DW.decimator_inphase_Sums[decimator_inphase_Sums_tmp] =
      final_lockin_P.decimator_inphase_FILT[decimator_inphase_Sums_tmp] *
      final_lockin_B.DigitalFilter;
  }

  if (final_lockin_DW.decimator_inphase_PhaseIdx - 1L == -1L) {
    coeffIdx_tmp = 192L;
    zCurr = final_lockin_DW.decimator_inphase_Sums[216L];
    for (n = 0; n < 9; n++) {
      zCurr += final_lockin_DW.decimator_inphase_Sums[coeffIdx_tmp];
      coeffIdx_tmp -= 24L;
    }

    final_lockin_DW.decimator_inphase_OutBuff = zCurr +
      final_lockin_DW.decimator_inphase_StatesBuff[0L];
  }

  if (final_lockin_M->Timing.RateInteraction.TID0_1) {
    /* S-Function (sdspfirdn2): '<Root>/decimator_inphase' */
    final_lockin_B.decimator_inphase = final_lockin_DW.decimator_inphase_OutBuff;
  }

  /* End of S-Function (sdspfirdn2): '<Root>/decimator_inphase' */

  /* DiscreteFir: '<S2>/Digital Filter' incorporates:
   *  Product: '<Root>/quadrature'
   */
  final_lockin_B.DigitalFilter_j = final_lockin_B.biasadjustment3 * rtb_sinusoid;
  rtb_sinusoid = 0.0;

  /* load input sample */
  for (n = 0; n < 75; n++) {
    /* shift state */
    zCurr = final_lockin_B.DigitalFilter_j;
    final_lockin_B.DigitalFilter_j = final_lockin_DW.DigitalFilter_states_a
      [(int32_T)n];
    final_lockin_DW.DigitalFilter_states_a[(int32_T)n] = zCurr;

    /* compute one tap */
    rtb_sinusoid += final_lockin_P.DigitalFilter_Coefficients_h[(int32_T)n] *
      zCurr;
  }

  /* compute last tap */
  /* store output sample */
  final_lockin_B.DigitalFilter_j = final_lockin_P.DigitalFilter_Coefficients_h
    [(int32_T)n] * final_lockin_B.DigitalFilter_j + rtb_sinusoid;

  /* End of DiscreteFir: '<S2>/Digital Filter' */

  /* S-Function (sdspfirdn2): '<Root>/decimatorquadrature' */
  coeffIdx_tmp = (int32_T)(final_lockin_DW.decimatorquadrature_PhaseIdx * 24LL);
  for (n = 0; n < 24; n++) {
    decimator_inphase_Sums_tmp = coeffIdx_tmp + n;
    final_lockin_DW.decimatorquadrature_Sums[decimator_inphase_Sums_tmp] =
      final_lockin_P.decimatorquadrature_FILT[decimator_inphase_Sums_tmp] *
      final_lockin_B.DigitalFilter_j;
  }

  if (final_lockin_DW.decimatorquadrature_PhaseIdx - 1L == -1L) {
    coeffIdx_tmp = 192L;
    zCurr = final_lockin_DW.decimatorquadrature_Sums[216L];
    for (n = 0; n < 9; n++) {
      zCurr += final_lockin_DW.decimatorquadrature_Sums[coeffIdx_tmp];
      coeffIdx_tmp -= 24L;
    }

    final_lockin_DW.decimatorquadrature_OutBuff = zCurr +
      final_lockin_DW.decimatorquadrature_StatesBuff[0L];
  }

  if (final_lockin_M->Timing.RateInteraction.TID0_1) {
    /* S-Function (sdspfirdn2): '<Root>/decimatorquadrature' */
    final_lockin_B.decimatorquadrature =
      final_lockin_DW.decimatorquadrature_OutBuff;
  }

  /* End of S-Function (sdspfirdn2): '<Root>/decimatorquadrature' */

  /* Update for S-Function (sdspfirdn2): '<Root>/decimator_inphase' */
  if (final_lockin_DW.decimator_inphase_PhaseIdx - 1L == -1L) {
    decimator_inphase_Sums_tmp = 1L;
    coeffIdx_tmp = 193L;
    for (n = 0; n < 22; n++) {
      zCurr = final_lockin_DW.decimator_inphase_Sums[coeffIdx_tmp + 24L];
      tempAccChanOffset = coeffIdx_tmp;
      for (iIdx = 0; iIdx < 9; iIdx++) {
        zCurr += final_lockin_DW.decimator_inphase_Sums[tempAccChanOffset];
        tempAccChanOffset -= 24L;
      }

      final_lockin_DW.decimator_inphase_StatesBuff[decimator_inphase_Sums_tmp -
        1L] = zCurr +
        final_lockin_DW.decimator_inphase_StatesBuff[decimator_inphase_Sums_tmp];
      decimator_inphase_Sums_tmp++;
      coeffIdx_tmp++;
    }

    zCurr = final_lockin_DW.decimator_inphase_Sums[coeffIdx_tmp + 24L];
    for (iIdx = 0; iIdx < 9; iIdx++) {
      zCurr += final_lockin_DW.decimator_inphase_Sums[coeffIdx_tmp];
      coeffIdx_tmp -= 24L;
    }

    final_lockin_DW.decimator_inphase_StatesBuff[decimator_inphase_Sums_tmp - 1L]
      = zCurr;
    final_lockin_DW.decimator_inphase_PhaseIdx = 10L;
  }

  final_lockin_DW.decimator_inphase_PhaseIdx--;

  /* End of Update for S-Function (sdspfirdn2): '<Root>/decimator_inphase' */

  /* Update for S-Function (sdspfirdn2): '<Root>/decimatorquadrature' */
  if (final_lockin_DW.decimatorquadrature_PhaseIdx - 1L == -1L) {
    decimator_inphase_Sums_tmp = 1L;
    coeffIdx_tmp = 193L;
    for (n = 0; n < 22; n++) {
      zCurr = final_lockin_DW.decimatorquadrature_Sums[coeffIdx_tmp + 24L];
      tempAccChanOffset = coeffIdx_tmp;
      for (iIdx = 0; iIdx < 9; iIdx++) {
        zCurr += final_lockin_DW.decimatorquadrature_Sums[tempAccChanOffset];
        tempAccChanOffset -= 24L;
      }

      final_lockin_DW.decimatorquadrature_StatesBuff[decimator_inphase_Sums_tmp
        - 1L] = zCurr +
        final_lockin_DW.decimatorquadrature_StatesBuff[decimator_inphase_Sums_tmp];
      decimator_inphase_Sums_tmp++;
      coeffIdx_tmp++;
    }

    zCurr = final_lockin_DW.decimatorquadrature_Sums[coeffIdx_tmp + 24L];
    for (iIdx = 0; iIdx < 9; iIdx++) {
      zCurr += final_lockin_DW.decimatorquadrature_Sums[coeffIdx_tmp];
      coeffIdx_tmp -= 24L;
    }

    final_lockin_DW.decimatorquadrature_StatesBuff[decimator_inphase_Sums_tmp -
      1L] = zCurr;
    final_lockin_DW.decimatorquadrature_PhaseIdx = 10L;
  }

  final_lockin_DW.decimatorquadrature_PhaseIdx--;

  /* End of Update for S-Function (sdspfirdn2): '<Root>/decimatorquadrature' */

  /* External mode */
  rtExtModeUploadCheckTrigger(2);
  rtExtModeUpload(0, (real_T)final_lockin_M->Timing.taskTime0);

  /* signal main to stop simulation */
  {                                    /* Sample time: [1.25E-5s, 0.0s] */
    if ((rtmGetTFinal(final_lockin_M)!=-1) &&
        !((rtmGetTFinal(final_lockin_M)-final_lockin_M->Timing.taskTime0) >
          final_lockin_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(final_lockin_M, "Simulation finished");
    }

    if (rtmGetStopRequested(final_lockin_M)) {
      rtmSetErrorStatus(final_lockin_M, "Simulation finished");
    }
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++final_lockin_M->Timing.clockTick0)) {
    ++final_lockin_M->Timing.clockTickH0;
  }

  final_lockin_M->Timing.taskTime0 = final_lockin_M->Timing.clockTick0 *
    final_lockin_M->Timing.stepSize0 + final_lockin_M->Timing.clockTickH0 *
    final_lockin_M->Timing.stepSize0 * 4294967296.0;
}

/* Model step function for TID1 */
void final_lockin_step1(void)          /* Sample time: [0.000125s, 0.0s] */
{
  real_T acc1;
  real_T acc1_0;
  real_T zCurr;
  int16_T n;
  uint16_T tmp;

  /* DiscreteFir: '<S3>/Digital Filter' */
  final_lockin_B.DigitalFilter_n = final_lockin_B.decimator_inphase;
  acc1 = 0.0;

  /* DiscreteFir: '<S4>/Digital Filter' */
  /* load input sample */
  /* compute last tap */
  /* store output sample */
  final_lockin_B.DigitalFilter_p = final_lockin_B.decimatorquadrature;
  acc1_0 = 0.0;

  /* load input sample */
  for (n = 0; n < 324; n++) {
    /* DiscreteFir: '<S3>/Digital Filter' */
    /* shift state */
    zCurr = final_lockin_B.DigitalFilter_n;
    final_lockin_B.DigitalFilter_n = final_lockin_DW.DigitalFilter_states_d
      [(int32_T)n];
    final_lockin_DW.DigitalFilter_states_d[(int32_T)n] = zCurr;

    /* compute one tap */
    acc1 += final_lockin_P.DigitalFilter_Coefficients_g[(int32_T)n] * zCurr;

    /* DiscreteFir: '<S4>/Digital Filter' */
    /* shift state */
    zCurr = final_lockin_B.DigitalFilter_p;
    final_lockin_B.DigitalFilter_p = final_lockin_DW.DigitalFilter_states_g
      [(int32_T)n];
    final_lockin_DW.DigitalFilter_states_g[(int32_T)n] = zCurr;

    /* compute one tap */
    acc1_0 += final_lockin_P.DigitalFilter_Coefficients_c[(int32_T)n] * zCurr;
  }

  /* DiscreteFir: '<S3>/Digital Filter' */
  final_lockin_B.DigitalFilter_n = final_lockin_P.DigitalFilter_Coefficients_g
    [(int32_T)n] * final_lockin_B.DigitalFilter_n + acc1;

  /* DiscreteFir: '<S4>/Digital Filter' incorporates:
   *  DiscreteFir: '<S3>/Digital Filter'
   */
  /* compute last tap */
  /* store output sample */
  final_lockin_B.DigitalFilter_p = final_lockin_P.DigitalFilter_Coefficients_c
    [(int32_T)n] * final_lockin_B.DigitalFilter_p + acc1_0;

  /* Sqrt: '<Root>/magnitude' incorporates:
   *  Math: '<Root>/inphasesquare'
   *  Math: '<Root>/quadraturesquare'
   *  Sum: '<Root>/inphaseandquadrature'
   */
  final_lockin_B.magnitude = sqrt(final_lockin_B.DigitalFilter_n *
    final_lockin_B.DigitalFilter_n + final_lockin_B.DigitalFilter_p *
    final_lockin_B.DigitalFilter_p);

  /* Product: '<Root>/gainscalingVout' incorporates:
   *  Constant: '<Root>/Constant2'
   */
  final_lockin_B.gainscalingVout = final_lockin_B.magnitude *
    final_lockin_P.Constant2_Value;

  /* MATLABSystem: '<Root>/DACvout' */
  acc1 = rt_roundd_snf(final_lockin_B.gainscalingVout);
  if (acc1 < 65536.0) {
    if (acc1 >= 0.0) {
      tmp = (uint16_T)acc1;
    } else {
      tmp = 0U;
    }
  } else {
    tmp = MAX_uint16_T;
  }

  MW_C2000DACSat(1U, tmp);

  /* End of MATLABSystem: '<Root>/DACvout' */

  /* Trigonometry: '<Root>/phase' incorporates:
   *  Product: '<Root>/ydivx'
   */
  final_lockin_B.phase = atan(final_lockin_B.DigitalFilter_p /
    final_lockin_B.DigitalFilter_n);
  rtExtModeUpload(1, (real_T)((final_lockin_M->Timing.clockTick1) * 0.000125));

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.000125, which is the step size
   * of the task. Size of "clockTick1" ensures timer will not overflow during the
   * application lifespan selected.
   */
  final_lockin_M->Timing.clockTick1++;
}

/* Model initialize function */
void final_lockin_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)final_lockin_M, 0,
                sizeof(RT_MODEL_final_lockin_T));
  rtmSetTFinal(final_lockin_M, -1);
  final_lockin_M->Timing.stepSize0 = 1.25E-5;

  /* External mode info */
  final_lockin_M->Sizes.checksums[0] = (2208331904U);
  final_lockin_M->Sizes.checksums[1] = (1892409540U);
  final_lockin_M->Sizes.checksums[2] = (1855738506U);
  final_lockin_M->Sizes.checksums[3] = (3341477560U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[3];
    final_lockin_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(final_lockin_M->extModeInfo,
      &final_lockin_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(final_lockin_M->extModeInfo,
                        final_lockin_M->Sizes.checksums);
    rteiSetTPtr(final_lockin_M->extModeInfo, rtmGetTPtr(final_lockin_M));
  }

  /* block I/O */
  (void) memset(((void *) &final_lockin_B), 0,
                sizeof(B_final_lockin_T));

  /* states (dwork) */
  (void) memset((void *)&final_lockin_DW, 0,
                sizeof(DW_final_lockin_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    final_lockin_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 15;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  {
    int16_T i;

    /* Start for S-Function (c2802xadc): '<Root>/ADCin' */
    /* Full-cycle Table lookup */
    if (MW_adcAInitFlag == 0) {
      InitAdcA();
      MW_adcAInitFlag = 1;
    }

    config_ADCA_SOC0 ();

    /* Full-cycle Table lookup */

    /* InitializeConditions for S-Function (sdspsine2): '<Root>/cosinusoid' */
    /* This code only executes when block is re-enabled in an
       enabled subsystem when the enabled subsystem states on
       re-enabling are set to 'Reset' */
    /* Reset to time zero on re-enable */
    /* Full-cycle Table lookup */
    final_lockin_DW.cosinusoid_TableIdx = 0U;

    /* InitializeConditions for DiscreteFir: '<S1>/Digital Filter' */
    for (i = 0; i < 75; i++) {
      final_lockin_DW.DigitalFilter_states[i] =
        final_lockin_P.DigitalFilter_InitialStates;
    }

    /* End of InitializeConditions for DiscreteFir: '<S1>/Digital Filter' */

    /* InitializeConditions for S-Function (sdspsine2): '<Root>/sinusoid' */
    /* This code only executes when block is re-enabled in an
       enabled subsystem when the enabled subsystem states on
       re-enabling are set to 'Reset' */
    /* Reset to time zero on re-enable */
    /* Full-cycle Table lookup */
    final_lockin_DW.sinusoid_TableIdx = 0U;

    /* InitializeConditions for S-Function (sdspfirdn2): '<Root>/decimator_inphase' */
    final_lockin_DW.decimator_inphase_PhaseIdx = 0L;
    memset(&final_lockin_DW.decimator_inphase_Sums[0], 0, 240U * sizeof(real_T));
    memset(&final_lockin_DW.decimator_inphase_StatesBuff[0], 0, 23U * sizeof
           (real_T));

    /* InitializeConditions for DiscreteFir: '<S2>/Digital Filter' */
    for (i = 0; i < 75; i++) {
      final_lockin_DW.DigitalFilter_states_a[i] =
        final_lockin_P.DigitalFilter_InitialStates_o;
    }

    /* End of InitializeConditions for DiscreteFir: '<S2>/Digital Filter' */

    /* InitializeConditions for S-Function (sdspfirdn2): '<Root>/decimatorquadrature' */
    final_lockin_DW.decimatorquadrature_PhaseIdx = 0L;
    memset(&final_lockin_DW.decimatorquadrature_Sums[0], 0, 240U * sizeof(real_T));
    memset(&final_lockin_DW.decimatorquadrature_StatesBuff[0], 0, 23U * sizeof
           (real_T));
    for (i = 0; i < 324; i++) {
      /* InitializeConditions for DiscreteFir: '<S3>/Digital Filter' */
      final_lockin_DW.DigitalFilter_states_d[i] =
        final_lockin_P.DigitalFilter_InitialStates_b;

      /* InitializeConditions for DiscreteFir: '<S4>/Digital Filter' */
      final_lockin_DW.DigitalFilter_states_g[i] =
        final_lockin_P.DigitalFilter_InitialStates_k;
    }

    /* Start for MATLABSystem: '<Root>/DACout' */
    MW_ConfigureDACA();

    /* Start for MATLABSystem: '<Root>/DACvout' */
    MW_ConfigureDACB();
  }
}

/* Model terminate function */
void final_lockin_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
