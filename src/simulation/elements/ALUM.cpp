#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_ALUM()
{
	Identifier = "DEFAULT_PT_ALUM";
	Name = "ALUM";
	Colour = 0xCDD0CB_rgb;
	MenuVisible = 1;
	MenuSection = SC_METAL;			// AlUM,COPR,BAUX,METL,BRMT,BMTL,SLCN,GOLD,TTAN,IRON,PTNM,BREC,TUNG - all moved to this category
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

	HeatConduct = 254;
	Description = "Aluminium, Highly conductive, corrodes IRON, dissipates heat over time";

	Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_HOT_GLOW;

    DefaultProperties.temp = R_TEMP + 273.15f;
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = 1.0f;
	HighPressureTransition = ST;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1220.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &update;
}
// eventually this element should have a powder form which reacts with brmt to create thermite (instead of brel/brec)
static int update(UPDATE_FUNC_ARGS)
{
    if (parts[i].temp>(R_TEMP+273.15f))
    {
        parts[i].temp = restrict_flt(parts[i].temp-0.005f, MIN_TEMP, MAX_TEMP);
    }
    else
    
    for (auto rx = -2; rx <= 2; rx++)
        {
            for (auto ry = -2; ry <= 2; ry++)
            {
                if (rx || ry)
                {
                    auto r = pmap[y+ry][x+rx];
                    if (!r)
                        continue;
                    if (TYP(r)==PT_IRON && sim->rng.chance(1, 300))
                    {
                        sim->create_part(i,x,y,PT_BAUX);
        
                    }
                }
            }
        }
    return 0;
}
