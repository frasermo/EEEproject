  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (final_lockin_P)
    ;%
      section.nData     = 12;
      section.data(12)  = dumData; %prealloc
      
	  ;% final_lockin_P.bias_Value
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% final_lockin_P.DigitalFilter_InitialStates
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% final_lockin_P.DigitalFilter_Coefficients
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% final_lockin_P.decimator_inphase_FILT
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 78;
	
	  ;% final_lockin_P.DigitalFilter_InitialStates_o
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 318;
	
	  ;% final_lockin_P.DigitalFilter_Coefficients_h
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 319;
	
	  ;% final_lockin_P.decimatorquadrature_FILT
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 395;
	
	  ;% final_lockin_P.Constant2_Value
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 635;
	
	  ;% final_lockin_P.DigitalFilter_InitialStates_b
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 636;
	
	  ;% final_lockin_P.DigitalFilter_Coefficients_g
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 637;
	
	  ;% final_lockin_P.DigitalFilter_InitialStates_k
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 962;
	
	  ;% final_lockin_P.DigitalFilter_Coefficients_c
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 963;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (final_lockin_B)
    ;%
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% final_lockin_B.ADCin
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% final_lockin_B.biasadjustment3
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% final_lockin_B.DigitalFilter
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% final_lockin_B.DigitalFilter_j
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% final_lockin_B.decimator_inphase
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% final_lockin_B.DigitalFilter_n
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% final_lockin_B.decimatorquadrature
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% final_lockin_B.DigitalFilter_p
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% final_lockin_B.magnitude
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% final_lockin_B.gainscalingVout
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% final_lockin_B.phase
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 3;
    sectIdxOffset = 1;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (final_lockin_DW)
    ;%
      section.nData     = 10;
      section.data(10)  = dumData; %prealloc
      
	  ;% final_lockin_DW.DigitalFilter_states
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% final_lockin_DW.decimator_inphase_Sums
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 75;
	
	  ;% final_lockin_DW.decimator_inphase_StatesBuff
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 315;
	
	  ;% final_lockin_DW.decimator_inphase_OutBuff
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 338;
	
	  ;% final_lockin_DW.DigitalFilter_states_a
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 339;
	
	  ;% final_lockin_DW.decimatorquadrature_Sums
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 414;
	
	  ;% final_lockin_DW.decimatorquadrature_StatesBuff
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 654;
	
	  ;% final_lockin_DW.decimatorquadrature_OutBuff
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 677;
	
	  ;% final_lockin_DW.DigitalFilter_states_d
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 678;
	
	  ;% final_lockin_DW.DigitalFilter_states_g
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 1002;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% final_lockin_DW.decimator_inphase_PhaseIdx
	  section.data(1).logicalSrcIdx = 10;
	  section.data(1).dtTransOffset = 0;
	
	  ;% final_lockin_DW.decimatorquadrature_PhaseIdx
	  section.data(2).logicalSrcIdx = 11;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% final_lockin_DW.cosinusoid_TableIdx
	  section.data(1).logicalSrcIdx = 14;
	  section.data(1).dtTransOffset = 0;
	
	  ;% final_lockin_DW.sinusoid_TableIdx
	  section.data(2).logicalSrcIdx = 15;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 2208331904;
  targMap.checksum1 = 1892409540;
  targMap.checksum2 = 1855738506;
  targMap.checksum3 = 3341477560;

