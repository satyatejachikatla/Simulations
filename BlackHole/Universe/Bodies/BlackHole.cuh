#ifndef SIMULATION_BLACKHOLE_UNIVERSE_BODIES_BLACKHOLE_
#define SIMULATION_BLACKHOLE_UNIVERSE_BODIES_BLACKHOLE_

#include <Universe/Bodies/Body.cuh>


class BlackHole : public Body {

private:
	double radius;
	double mass;

public:
	BlackHole();
	~BlackHole();
};

#endif /*SIMULATION_BLACKHOLE_UNIVERSE_BODIES_BLACKHOLE_*/