#include "regulation.h"

float regulationTest(int regul, float csgn, float *tabT, int nT)
{
	float cmd = 100.0; // Default power command at 100%
	int i;

	for (i = 1; i < nT; i++) // Do the regulation test nT times
	{
		cmd = regulation(10 + regul, csgn, tabT[i], tabT[i - 1]); // +10 for the the tests modes
	}

	return cmd;
}

float regulation(int mode, float target, float temp, float prev_temp)
{
	switch (mode)
	{
	case NORMAL_TOR:  // ToR
	case TEST_TOR: // ToR for the regulation automatic Test
		return (temp < target) ? TOR_FULL_POWER : TOR_LOW_POWER;
		break;

	case NORMAL_PID: // Optimized PID
		return regulation_pid(target, temp, prev_temp);
		break;

	case TEST_PID: // Normal PID for automatic test
		return regulation_pid_test(target, temp, prev_temp);
		break;

	default: // Invalid mod given
		fprintf(stderr, "Error : mode %d is invalid !", mode);

		return 0;
		break;
	}
}

float regulation_pid(float target, float temp, float prev_temp)
{
	float pid = 0, p, i, d;

	p = PID_OPT_KP * (target - temp);					 // Kp*(error)
	i = PID_OPT_KI * regulation_error_sum(target, temp); // Ki*(sum of errors)
	d = PID_OPT_KD * (prev_temp - temp);				 // Kd*(error-last_error)
	pid = p + i + d;

	if (pid < 0) // Saturation case (under 0)
	{
		pid = 0;
		regulation_error_sum(-target, -temp); // Substract error to mitigate the impact of saturated errors in the Integrative factor
	}
	else if (pid > 100) // Saturation case (over 100)
	{
		pid = 100;
		regulation_error_sum(-target, -temp); // Substract error to mitigate the impact of saturated errors in the Integrative factor
	}

	printf("T:%.4f\tC:%.4f\tP:%.4f\tI:%.4f\tD:%.4f\tOut:%.4f\n\n", target, temp, p, i, d, pid); // Debug

	return pid;
}

float regulation_error_sum(float target, float current)
{
	static float i = 0; // "i" keep the previous value

	return i += (target - current); // add the error
}

float regulation_pid_test(float target, float temp_now, float temp_prev)
{
	static float i = 0; // "i" keep the previous value
	float pid;
	float error = target - temp_now;		// Current error
	float error_prev = target - temp_prev;	// Previous error

	i += (SAMPLE_RATE * error + (SAMPLE_RATE * (error_prev - error)) / 2); // Local integration of the error

	pid = PID_KP * error + PID_KI * i + PID_KD * (error - error_prev) / SAMPLE_RATE; // yup

	if (pid < 0) // Saturation (under 0)
	{
		pid = 0;
	}
	else if (pid > 100) // Saturation (over 100)
	{
		pid = 100;
	}

	return pid;
}