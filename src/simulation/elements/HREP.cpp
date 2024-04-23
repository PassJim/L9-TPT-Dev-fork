#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_HREP()
{
	Identifier = "DEFAULT_PT_HREP";
	Name = "HREP";
	Colour = 0x708090_rgb;
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 99;

	Weight = 80;

	DefaultProperties.temp = R_TEMP - 2.0f + 273.15f;
	HeatConduct = 29;
	Description = "Liquid nano repair";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = 0.5f;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 350.0f;
	HighTemperatureTransition = PT_HNAN;

	//Update = &update;
}

/**static int update(UPDATE_FUNC_ARGS)
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
				case PT_HLOY:
					if (sim->rng.chance(1, 100))
						sim->create_part(ID(r),x+rx,y+ry,PT_HLOY);
					break;
				
                case PT_HSTR:
					if (sim->rng.chance(1, 100))
						sim->create_part(ID(r),x+rx,y+ry,PT_HSTR);
					break;
				
                case PT_BMTL:
					if (sim->rng.chance(1, 100))
						sim->create_part(ID(r),x+rx,y+ry,PT_BMTL);
					break;
				
                case PT_METL:
					if (sim->rng.chance(1, 100))
						sim->create_part(ID(r),x+rx,y+ry,PT_METL);
					break;
				
                case PT_IRON:
					if (sim->rng.chance(1, 100))
						sim->create_part(ID(r),x+rx,y+ry,PT_IRON);
					break;
				
                }
			
            }
        }
    }
	
	return 0;

}	
/**/
