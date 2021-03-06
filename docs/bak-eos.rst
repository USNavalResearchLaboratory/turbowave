Equations of State (EOS)
=========================

The Equation of State (EOS) tools calculate thermodynamic quantities (such as pressure, :math:`P`, and Temperature, :math:`T` ) from fluid quantities (such as energy density, :math:`u`, and particle density, :math:`n`). In other words, each EOS tool represents a set of functions such as :math:`P(n,u)` and :math:`T(n,u)`. Some EOS tools are useful for a restricted class of problems, such as ideal gases. Others utilize tables generated by other software and can, in principle, be very general.  The user selects the tools, and therefore the EOS models, to associate with a given hydrodynamic simulation.

.. csv-table:: Table I. Symbols.
	:header: "Symbol", "Quantity", "SI Units"

	:math:`n`, "Particle Density", :math:`{\rm m}^{-3}`
	:math:`\rho`, "Mass Density", :math:`{\rm kg}/{\rm m}^3`
	:math:`u`, "Energy Density", :math:`{\rm J}/{\rm m}^3`
	:math:`v`, "Velocity", :math:`{\rm m}/{\rm s}`
	:math:`V`, "Specific Volume", :math:`{\rm m}^3`
	:math:`\epsilon`, "Specific Internal Energy", :math:`{\rm J}/{\rm kg}`
	:math:`E`, "Internal Energy", :math:`{\rm J}`
	:math:`C_v`, "Specific Heat at Constant Volume", :math:`{\rm J}/{\rm kg}\cdot{\rm K}`

There are two types of EOS relations that need to be specified to describe the material completely: the thermal EOS gives :math:`P(n,T)`, and the caloric EOS gives :math:`\epsilon(n,T)`. In many applications the caloric EOS reduces to a constant specific heat, :math:`C_v`, with the relation :math:`d\epsilon = C_v dT`.

.. Note::

	All hydrodynamics simulations require an EOS to close the system of equations.  TurboWAVE hydrodynamics modules will automatically install an ideal gas EOS if no other model is specified.

The Principle Hugoniot
----------------------

The Rankine-Hugoniot relations are relevant to EOS models that use a point along the Hugoniot as a reference point for a broader calculation of EOS. These relations constrain the mass, momentum, and energy just upstream of a shock front. The collection of possible upstream states, in the case of vanishing downstream velocity and pressure, is called the principle Hugoniot. There are an infinite number of possible Hugoniots for arbitrary downstream conditions, but there is only one principle Hugoniot. The principle Hugoniot for a given material is closely related to its EOS.  Experimental measurements of shock and fluid velocities in a given material can be used to establish its principle Hugoniot, and therefore its EOS.

The Hugoniot relations express the conservation of mass, momentum, and energy. Suppose that a planar shock front moves through a fluid at speed :math:`D`. The pressure and density of the material prior to the passing of the shock front are :math:`P_0` and :math:`\rho_0`, respectively. Immediately after the shock passes the pressure and density are :math:`P` and :math:`\rho`. Similarly, :math:`V` and :math:`V_0` are the upstream and downstream specific volumes, respectively, and :math:`\epsilon` and :math:`\epsilon_0` are the upstream and downstream specific internal energies.

An outline how the principle Hugoniot is determined is as follows (see Ref. [1] for detailed discussion). First one needs the three Rankine-Hugoniot relations.  Setting the quantity of mass entering and leaving the shock as equal (conservation of mass) gives

:math:`\rho ( D - v ) = \rho_0 ( D - v_0 ).`

The change in momentum density across the shock front is due to the impulse associated with the pressure difference, leading to

:math:`P - P_0 = \rho_0 (D - v_0) (v - v_0).`

The work done by the pressure (PV work) gives the change in internal energy, i.e.,

:math:`E - E_0 = \frac{1}{2} (P + P_0) (V - V_0).`

Experimentally, data for :math:`D` and :math:`v` are collected by inducing a shock in a substance and observing its propagation.  The upstream density, pressure, and energy are then fixed by the Rankine-Hugoniot relations, assuming the downstream conditions are known. The principle Hugoniot is generated if the downstream conditions satisfy :math:`P_0 \approx 0` and :math:`v_0 \approx 0`.

The important point is that a relationship between :math:`D` and :math:`v` fixes the principle Hugoniot.  For most solids this relationship is found to be nearly linear:

:math:`D \approx c_0 + S_1 v.`

where the y-intercept :math:`c_0` and the slope :math:`S_1` are the parameters of a linear fit to the experimental data.  The parameter :math:`c_0` is usually close to the speed of sound in the material.  Once this linear fit is obtained, the relationship between density, pressure, and energy is effectively known.

Mie Gruneisen EOS Theory
-------------------------

The simplest EOS implemented in Turbowave, other than the default ideal gas model, is the Mie-Gruneisen EOS, which is often used to describe a shock-compressed solid. It is an example of an incomplete EOS, as it only provides the pressure, and not the temperature, as a function of the internal energy. A basic assumption of the Mie Gruneisen model is that the thermal energy of a material is adequately described as the sum of the energies of a collection of simple harmonic oscillators with frequencies :math:`\nu_i(V)`, which are functions of volume only. It neglects electronic contributions to the internal energy.

A detailed derivation of this EOS is given in Ref. [1]. Here we give a basic outline. Given the physical description detailed above, the Helmholtz free energy for the system is

:math:`F(T,V) = \phi(V) + \sum_{i=1}^{3 N} \frac{h \nu_i(V)}{2} + k T \sum_{i=1}^{3 N}\ln(1 - e^{-h \nu_i(V)/kT}),`

where :math:`\phi(V)` is the potential energy of the material with :math:`N` atoms in a total volume, :math:`V`. The sum is over the :math:`3 N` oscillator modes. The pressure is given by :math:`P = - ( \partial F/\partial V)_T`, which when expanded results in various derivatives of :math:`\nu_i (V)`. Defining

:math:`\gamma_i \equiv -\frac{d \ln v_i}{d \ln V} = -\frac{V}{\nu_i} \left( \frac{d v_i}{d V} \right),`

and assuming :math:`\gamma_i = \gamma_G = {\rm constant}`, gives the pressure as a function of vibrational energy. If the internal energy is a sum of vibrational and potential energy (:math:`E = E_\text{vib} + \phi(V)`), this finally reduces to

:math:`P - P_R = \frac{\gamma_G}{V} (E - E_R),`

where :math:`P_R` and :math:`E_R` are reference values of pressure and internal energy, which are assumed known on some curve such as a Hugoniot. The quantity :math:`\gamma_G` is called the Gruneisen parameter, and is defined by

:math:`\gamma_G = V \left( \frac{\partial P}{\partial E} \right)_V.`

The numerical value of :math:`\gamma_G` for a given material at a given density can be experimentally measured, and is tabulated in various references (e.g., Refs. [2] and [3]).

In summary, the Gruneisen parameter describes the effect that changing the volume (and spacing) of a crystal lattice has on its vibrational energy, and consequently on its response to pressure forces.

Mie Gruneisen EOS Implementation
---------------------------------

Various implementations of a Mie-Gruneisen EOS are possible, depending on how :math:`\gamma_G`, :math:`P_R`, and :math:`E_R`, are specified. There are two different Mie Gruneisen implementations currently available in turboWAVE. Both use the default caloric EOS :math:`d\epsilon = C_v dT` with constant :math:`C_v`.

		.. py:function:: eos = simple-mie-grunseisen

			Treats :math:`\gamma_G` as a constant user-specified value, and takes :math:`E_R = P_R = 0`. This model is only useful for qualitative studies.

		.. py:function:: eos = linear-mie-grunseisen

			Assumes the Gruneisen coefficient satisfies :math:`\gamma_G(\rho) = \gamma_G(\rho_R)\rho_R/\rho`, with :math:`\rho_R` a reference density, and derives :math:`P_R` and :math:`E_R` from a linear Hugoniot fit. As a result, four parameters must be specified: The y-intercept of the Hugoniot, :math:`c_0`, and the slope of the linear fit, :math:`S_1`, the Gruneisen parameter, and the reference density at which it is known.

More complex implementations of the Mie Gruneisen EOS may be added in the future, such as a cubic interpolation of the Hugoniot and/or allowance for a small nonlinear dependence of :math:`\gamma_G` on specific volume. In addition, a different caloric EOS may be implemented in combination with these models.

References
-----------
[1] Gathers, R. G., "Selected Topics in Shock Wave Physics and Equation of State Modeling", World Scientific (1994).

[2] Marsh, S. P., ed., "LASL Shock Hugoniot Data", University of California Press (1980)

[3] McQueen, R. G., Marsh, S. P, *Equation of State for Nineteen Elements from Shock-Wave Measurements to Two Megabars*, J. Appl. Phys **31**, 1253-1269 (1960)
