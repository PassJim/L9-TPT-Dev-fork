#include "simulation/ElementCommon.h"
#include <vector>

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);

std::vector<int> reactTypes = {PT_WATR,PT_DSTW,}; // corrodes element below

void Element::Element_COPR()
{
	Identifier = "DEFAULT_PT_COPR";
	Name = "COPR";
	Colour = 0xAF6A49_rgb;
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
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
	Hardness = 1;

	Weight = 100;

	HeatConduct = 251;
	Description = "Copper, patinas if wet, Highly conductive, dissipates heat over time";

	Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = 1.0f;
	HighPressureTransition = ST;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1983.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &update;
    Graphics = &graphics;

}

static int update(UPDATE_FUNC_ARGS)
{
 for (auto rx = -4; rx <= 4; rx++)
        {
            for (auto ry = -4; ry <= 4; ry++)
            {
                if (rx || ry)
                {
                    auto r = pmap[y+ry][x+rx];
                    if (!r)
                        continue;
                    if (TYP(r)==PT_MWAX && sim->rng.chance(1, 300))
                    {   
                        if (parts[i].tmp>0)
                            {
                             parts[i].tmp-=2;
                            }
                        
                       
        
                    }
                }
            }
        }

   
 if (parts[i].temp>(R_TEMP+500.0f))
    {
        parts[i].temp = restrict_flt(parts[i].temp-0.01f, MIN_TEMP, MAX_TEMP);
    }

    for (auto rx = -4; rx <= 4; rx++)
	{
		for (auto ry = -4; ry <= 4; ry++)
		{
			if (rx || ry)
			{
				auto r = pmap[y+ry][x+rx];
				if (!r)
					continue;
                if(TYP(r)==PT_SLTW)
                    {
                        if (sim->rng.chance(1, 100))
                            {
                        
                                parts[i].tmp+=1;
                            }    
                    }

                else

				for (int reactType:reactTypes)
                {
                    if(TYP(r)==reactType)
                    {                
                        if (sim->rng.chance(1, 1000))
                            {
                        
                                parts[i].tmp+=1;
                            }
                    }
                }   
			}
		}
			
	}
	return 0;
}
static int graphics(GRAPHICS_FUNC_ARGS) //target colour of green hue 28 r 115 g 85 b
{
	*colr -= cpart->tmp;
	*colg += cpart->tmp;
	*colb += cpart->tmp;
	if (*colr<=28)
		*colr = 28;
	if (*colg>=115)
		*colg = 115;
	if (*colb>=85)
		*colb = 85;
	return 0;
}