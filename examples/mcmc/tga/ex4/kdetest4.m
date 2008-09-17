stage0Output

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Plots on parameters
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
a = 1;
if a > 0

plot(stage0_calib_bmc_0_chain_centersOfHistBins(1,:),stage0_calib_bmc_0_chain_histBins(1,:),'o');
waitforbuttonpress; %sleep(3);
clf;

plot(stage0_calib_bmc_0_chain_centersOfHistBins(2,:),stage0_calib_bmc_0_chain_histBins(2,:),'o');
waitforbuttonpress;
clf;

plot(stage0_calib_bmc_0_chain_kdeEvalPositions(1,:),stage0_calib_bmc_0_chain_gaussianKdeDensities(1,:),'o'); 
waitforbuttonpress;
clf;

plot(stage0_calib_bmc_0_chain_kdeEvalPositions(2,:),stage0_calib_bmc_0_chain_gaussianKdeDensities(2,:),'o');
waitforbuttonpress;
clf;

end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Plots on qois
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
plot(stage0_propag_mc_seq_centersOfHistBins(1,:),stage0_propag_mc_seq_histBins(1,:),'o');
waitforbuttonpress;
clf;

plot(stage0_propag_mc_seq_kdeEvalPositions(1,:),stage0_propag_mc_seq_gaussianKdeDensities(1,:),'o'); 

