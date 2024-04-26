#include "simulation/ElementCommon.h"
#include "simulation/Air.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_HSTR()
{
	Identifier = "DEFAULT_PT_HSTR";
	Name = "HSTR";
	Colour = 0x729493_rgb;
	MenuVisible = 1;
	MenuSection = SC_MOD;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 1;
	Hardness = 50;

	Weight = 100;

	HeatConduct = 251;
	Description = "High Strength Human Alloy, similar properties to titanium";

	Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_HOT_GLOW|PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1941.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &update;
}
static int update(UPDATE_FUNC_ARGS)
{	
	for (auto rx = -1; rx <= 1; rx++)
	{
		for (auto ry = -1; ry <= 1; ry++)
		{
			if (rx || ry)
			{
				auto r = pmap[y+ry][x+rx];
				switch (TYP(r))
				{
			
				//converts Metals
				case PT_BREC:
					if (sim->rng.chance(1, 1000))
						sim->create_part(ID(r),x+rx,y+ry,PT_HSTR);
					break;
				
				}
			}
	}
	
	return 0;
	}
	int HSTR = 0;
	if (nt <= 2)
		HSTR = 2;
	else if (parts[i].tmp)
		HSTR = 2;
	else if (nt <= 6)
	{
		for (int rx = -1; rx <= 1; rx++)
		{
			for (int ry = -1; ry <= 1; ry++)
			{
				if (!rx != !ry)
				{
					if (TYP(pmap[y+ry][x+rx]) == PT_HSTR)
						HSTR++;
				}
			}
		}
	}

	return 0;
}
