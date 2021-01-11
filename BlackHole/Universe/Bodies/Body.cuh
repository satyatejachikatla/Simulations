#ifndef SIMULATION_BLACKHOLE_UNIVERSE_BODIES_BODY_
#define SIMULATION_BLACKHOLE_UNIVERSE_BODIES_BODY_


class Body {

private:


public:
	Body();

	virtual double GetAccelerationDuetoGravity(double distance) = 0;
	virtual ~Body();
};

#endif /*SIMULATION_BLACKHOLE_UNIVERSE_BODIES_BODY_*/