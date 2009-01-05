%string1 = sprintf('Refer: A=%9.3e, E=%9.3e',case3_refA,case3_refE);
%string2 = sprintf('Guess: A=%9.3e, E=%9.3e',case3_guessA,case3_guessE);

case3_;
case4_;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
plot(case3_refW_Time,case3_refW_Value,'+k','linewidth',2);
hold
plot(case3_w_Time,case3_w_Value,'-b','linewidth',2);
plot(case4_w_Time,case4_w_Value,'-r','linewidth',2);

ylabel('w','fontsize',20);
xlabel('time (s)','fontsize',20);
title('Evolution of mass fraction','fontsize',20);
grid minor;
set(gca,'fontsize',20);
legend('Reference',...
       'Case3',...
       'Case4',...
       'location','southwest');
print -dpng case3_case4_w.png
waitforbuttonpress
clf;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
plot(case3_refW_Time,case3_refW_Value,'+k','linewidth',3);
hold
plot(case3_w_Time,case3_w_Value, '-b','linewidth',3);
plot(case4_w_Time,case4_w_Value, '-r','linewidth',3);
a = axis;
axis([8000 9600 a(3) a(4)]);

ylabel('w','fontsize',20);
xlabel('time (s)','fontsize',20);
title('Zoom of the evolution of mass fraction','fontsize',20);
grid minor;
set(gca,'fontsize',20);
legend('Reference',...
       'Case3',...
       'Case4',...
       'location','southwest');
print -dpng case3_case4_w_zoom.png
waitforbuttonpress
clf;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
plot(case3_wA_Time,case3_wA_Value,'-b','linewidth',3);
hold
plot(case4_wA_Time,case4_wA_Value,'-r','linewidth',3);

ylabel('w_A','fontsize',20);
xlabel('time (s)','fontsize',20);
title('w_A','fontsize',20);
grid minor;
set(gca,'fontsize',20);
legend('Case3',...
       'Case4',...
       'location','southwest');
print -dpng case3_case4_wA.png
waitforbuttonpress
clf;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
plot(case3_wE_Time,case3_wE_Value,'-b','linewidth',3);
hold
plot(case4_wE_Time,case4_wE_Value,'-r','linewidth',3);

ylabel('w_E','fontsize',20);
xlabel('time (s)','fontsize',20);
title('w_E','fontsize',20);
grid minor;
set(gca,'fontsize',20);
legend('Case3',...
       'Case4',...
       'location','southwest');
print -dpng case3_case4_wE.png
waitforbuttonpress
clf;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
plot(case3_lambda_Time,case3_lambda_Value,'-b','linewidth',3);
hold
plot(case4_lambda_Time,case4_lambda_Value,'-r','linewidth',3);

ylabel('\lambda','fontsize',20);
xlabel('time (s)','fontsize',20);
title('\lambda','fontsize',20);
grid minor;
set(gca,'fontsize',20);
legend('Case3',...
       'Case4',...
       'location','southwest');
print -dpng case3_case4_lambda.png
waitforbuttonpress
clf;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
plot(case3_lambdaA_Time,case3_lambdaA_Value,'-b','linewidth',3);
hold
plot(case4_lambdaA_Time,case4_lambdaA_Value,'-r','linewidth',3);

ylabel('\lambda_A','fontsize',20);
xlabel('time (s)','fontsize',20);
title('\lambda_A','fontsize',20);
grid minor;
set(gca,'fontsize',20);
legend('Case3',...
       'Case4',...
       'location','southwest');
print -dpng case3_case4_lambdaA.png
waitforbuttonpress
clf;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
plot(case3_lambdaE_Time,case3_lambdaE_Value,'-b','linewidth',3);
hold
plot(case4_lambdaE_Time,case4_lambdaE_Value,'-r','linewidth',3);

ylabel('\lambda_E','fontsize',20);
xlabel('time (s)','fontsize',20);
title('\lambda_E','fontsize',20);
grid minor;
set(gca,'fontsize',20);
legend('Case3',...
       'Case4',...
       'location','southwest');
print -dpng case3_case4_lambdaE.png
waitforbuttonpress
clf;

