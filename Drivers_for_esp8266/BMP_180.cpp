
#include "SFE_BMP180.h"
#include "Wire.h"
#include "BMP_180.h"
// You will need to create an SFE_BMP180 object, here called "pressure":

SFE_BMP180 pressure;




class BMP180_PROCESSING
{
public:
	boolean bBMP180CalibrationDone = false;

	double dBMPPressure;
	double dBMPAbsolutePressure;
	double dBMPTemperature;
	double dBMPAltitude;

private:

};


BMP180_PROCESSING  BMP180_data;



void vInit_BMP180()
{
	//Serial.begin(115200);
	if (pressure.begin())
	{
		Serial.println("BMP180 init success");
	}
		
	else
	{
		// Oops, something went wrong, this is usually a connection problem,
		// see the comments at the top of this sketch for the proper connections.

		Serial.println("BMP180 init fail\n\n");
		
	}
}


void vProcess_BMP180_data()
{
	char status;
	double T, P, p0, a;

	// Loop here getting pressure readings every 10 seconds.

	// If you want sea-level-compensated pressure, as used in weather reports,
	// you will need to know the altitude at which your measurements are taken.
	// We're using a constant called ALTITUDE in this sketch:
	Serial.println();
	Serial.print("provided altitude: ");
	Serial.print(ALTITUDE, 0);
	Serial.print(" meters, ");

	// If you want to measure altitude, and not pressure, you will instead need
	// to provide a known baseline pressure. This is shown at the end of the sketch.

	// You must first get a temperature measurement to perform a pressure reading.

	// Start a temperature measurement:
	// If request is successful, the number of ms to wait is returned.
	// If request is unsuccessful, 0 is returned.

	status = pressure.startTemperature();
	if (status != 0)
	{
		// Wait for the measurement to complete:
		delay(status);

		// Retrieve the completed temperature measurement:
		// Note that the measurement is stored in the variable T.
		// Function returns 1 if successful, 0 if failure.

		status = pressure.getTemperature(T);
		if (status != 0)
		{
			BMP180_data.dBMPTemperature = T;
			// Start a pressure measurement:
			// The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
			// If request is successful, the number of ms to wait is returned.
			// If request is unsuccessful, 0 is returned.
			status = pressure.startPressure(3);
			if (status != 0)
			{
				// Wait for the measurement to complete:
				delay(status);

				// Retrieve the completed pressure measurement:
				// Note that the measurement is stored in the variable P.
				// Note also that the function requires the previous temperature measurement (T).
				// (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
				// Function returns 1 if successful, 0 if failure.

				status = pressure.getPressure(P, T);
				if (status != 0)
				{
					BMP180_data.dBMPAbsolutePressure = P;

					p0 = pressure.sealevel(P, ALTITUDE); // we're at 44 meters (Nicolina, Iasi)

					BMP180_data.dBMPPressure = p0;
					// Parameters: P = absolute pressure in mb, p0 = baseline pressure in mb.
					// Result: a = altitude in m.

					a = pressure.altitude(P, p0);
					BMP180_data.dBMPAltitude = a;
					Serial.println();
					Serial.print(a,2);
				}
				else Serial.println("error retrieving pressure measurement\n");
			}
			else Serial.println("error starting pressure measurement\n");
		}
		else Serial.println("error retrieving temperature measurement\n");
	}
	else Serial.println("error starting temperature measurement\n");

	//delay(5000);  // Pause for 5 seconds.
}