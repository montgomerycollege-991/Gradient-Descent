#include <stdio.h>
#include <random>

struct vec2 {

	double x;
	double y;
};

void main() {

	//loss function = (2-(I+S))^2+(5-(I+(2*S)))^2+(10-(I+(4*S)))^2+(18-(I+(9*S)))^2

	//derivative of loss function with respect to I
	// = -2(2-(I+S))-2(5-(I+(2*S))-2(10-(I+(4*S)))-2(18-(I+(9*S))

	//derivative of loss function with respect to S
	// = -2(2-(I+S))-4(5-(I+(2*S))-18(18-(I+(9*S))

	double learningrate = .000001; //learning rate

	auto calculate_gradient = [&](double slope,double intercept)->vec2 { //function to calculate gradient
		double gradient_Idirection = 8 * intercept + 32 * slope - 70;
		double gradient_Sdirection = 32 * intercept + 204 * slope - 428;
		return vec2{ gradient_Sdirection,gradient_Idirection }; //return a vector containing "x slope" and "y slope"
	};

	double Slope = (double)rand(); //  pick a random value for intial slope
	double Intercept = (double)rand(); // pick a random value for initial intercept

	vec2 current_gradient = calculate_gradient(Slope, Intercept); //initial gradient
	//printf("slope gradient: %f  intercept gradient: %f\n", current_gradient.x, current_gradient.y);=

	int xsign = 1;
	int ysign = 1;

	vec2 last_gradient = { 0,0 };

	while (abs(current_gradient.x)>.0000001 || abs(current_gradient.y)>.0000001 ) { // take .1 to be an acceptable error margin

		//printf("slope gradient: %f  intercept gradient: %f\n", current_gradient.x, current_gradient.y);

		Slope -= xsign*current_gradient.x * learningrate; //increase predicted slope by current gradient*learningrate

		Intercept -= (ysign*current_gradient.y * learningrate);//increase predicted intercept by current gradient*learningrate

		current_gradient = calculate_gradient(Slope,Intercept); //increase S
		
		//make sure we are getting closer to a zero gradient vector
		if (last_gradient.x && (abs(last_gradient.x) < abs(current_gradient.x)))  xsign *= -1;
		if (last_gradient.y && (abs(last_gradient.y) < abs(current_gradient.y)))  ysign *= -1;

		last_gradient = current_gradient;
	}


	printf("calculated intercept: %f  calculated slope: %f\n",Intercept, Slope);
	getchar();
}