#include "simulation/ElementCommon.h"
#include <algorithm>

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);

void Element::Element_HUMN()
{
	Identifier = "DEFAULT_PT_HUMN";
	Name = "HUMN";
	Colour = 0xADCC7E_rgb;
	MenuVisible = 1;
	MenuSection = SC_MOD;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.95f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 400;
	Explosive = 0;
	Meltable = 0;
	Hardness = 50;
	PhotonReflectWavelengths = 0x0007C000;

	Weight = 100;

	HeatConduct = 65;
	Description = "Human, Similar to plant, but drinks Y-Fuel";

	Properties = TYPE_SOLID|PROP_NEUTPENETRATE|PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 573.0f;
	HighTemperatureTransition = PT_FIRE;

	Update = &update;
	Graphics = &graphics;
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
				case PT_YFUL:
					if (sim->rng.chance(1, 500))
					{	
						auto np = sim->create_part(ID(r),x+rx,y+ry,PT_HUMN);
						if (np<0) continue;
						parts[np].life = 0;
					}

					break;
					
					
				case PT_EXOT:
					if (sim->rng.chance(1, 1000))
					
						goto succ;	
						
					break;
			
					
				case PT_DEUT:
					if (sim->rng.chance(1, 1000))
					
						goto succ2;

					break;
				
				default:
					continue;
				}
			}
		}
	}
	return 0;
	succ:
		sim->part_change_type(i,x,y,PT_PLNT);
		return 0;
	succ2:
		sim->create_part(i,x,y,PT_BANG);
		return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	float maxtemp = std::max((float)cpart->tmp2, cpart->temp);
	if (maxtemp > 300)
	{
		*colr += (int)restrict_flt((maxtemp-300)/5,0,58);
		*colg -= (int)restrict_flt((maxtemp-300)/2,0,102);
		*colb += (int)restrict_flt((maxtemp-300)/5,0,70);
	}
	if (maxtemp < 273)
	{
		*colg += (int)restrict_flt((273-maxtemp)/4,0,255);
		*colb += (int)restrict_flt((273-maxtemp)/1.5,0,255);
	}
	return 0;
}