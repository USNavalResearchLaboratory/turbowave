Input File: Fluids
==================

Relativistic Cold Fluid
-----------------------

The following object generates a module that computes the motion of a cold, relativistic, electron fluid.  It is assumed there is an immobile background of ions.  Temperature only comes into the computation of the Coulomb collision frequency.  The electron temperature is controlled by the last ``generate`` block (see :ref:`matter-loading`).  There can only be one cold fluid module in a simulation.  Electron, ion, and neutral density are tracked in this one module.  Any profiles installed for the fluid refer to a gas with constant fractional ionization.

.. py:function:: new fluid <name> { <directives> }

	:param str name: assigns a name to the fluid
	:param block directives: The following directives are supported:

		Installable tools: :ref:`ionization`

		.. py:function:: charge = q

			:param float q: charge of the fluid constituent, usually electrons

		.. py:function:: mass = m

			:param float m: mass of the fluid constituent, usually electrons

		.. py:function initial ionization fraction = f

			:param float f: ratio of initial electron density to neutral + ion density

		.. py:function:: neutral cross section = sigma

		 	:param float sigma: electron-neutral collision cross section

		.. py:function:: coulomb collisions = cc

		 	:param bool cc: if true, add collision frequency based on Coulomb cross section to neutral collision frequency

		.. note::
			the ion species and electron species variables (see :ref:`ionization`) have no meaning here


SPARC Hydro Modules
-------------------

.. py:function:: new hydrodynamics [<name>] { <directives> }

	This is the top level SPARC module.  Internally it contains and manages all other SPARC modules.

	:param str name: name given to the hydro manager
	:param block directives: The following directives are supported:

		Installable tools: :ref:`elliptic`

		.. py:function:: epsilon factor = eps

			:param float eps: error tolerance for adaptive time step

		.. py:function:: background density = n0

			:param float n0: automatically create a uniform background density ``n0`` for every chemical species.  Charged species are automatically weighted such that neutrality is maintained.  Defaults to zero, in which case the user is responsible for explicitly loading every chemical species.

		.. py:function:: background temperature = T0

			:param float T0: temperature to use for the background fluid. If the background density is nonzero this must be set to a positive value.

		.. py:function:: radiation model = rad

		 	:param enum rad: takes values ``thick``, ``thin``, ``none``

		.. py:function:: laser model = las

		 	:param enum las: takes values ``vacuum``, ``isotropic``

		.. py:function:: plasma model = plas

			:param enum plas: takes values ``neutral``, ``quasineutral``

		.. py:function:: electrostatic heating = esh

			:param bool esh: If ``on``, electrons are heated by self-consistent electrostatic fields. Default is ``off``.

		.. py:function:: dipole center = Dx Dy Dz

		 	Reference point for dipole moment diagnostic


.. _chemical:

.. py:function:: new chemical [<name>] [for <name>] { <directives> }

	The ``chemical`` module uses automatic attachment, i.e., if a ``chemical`` is created at the root level without the ``for`` clause a new equilibrium group module is created for it automatically.  As a result, ``chemical`` modules should never be attached using ``get`` statements.

	:param str name: name given to the chemical species
	:param block directives: The following directives are supported:

		Installable tools: :ref:`ionization`, :ref:`eos`

		.. py:function:: mass = m0

			:param float m0: mass of the constituent particles, default = 1.0

		.. py:function:: charge = q0

			:param float q0: charge of the constituent particles, default = -1.0

		.. py:function:: cv = cv0

		 	:param float cv0: normalized specific heat at constant volume, :math:`mc_v/k_B`, a typical value is 1.5 for species with no internal degrees of freedom.

		.. py:function:: vibrational energy = epsv

		 	:param float epsv: energy between vibrational levels, default = 0 = no vibrations

		.. py:function:: implicit = tst

		 	:param bool tst: whether to use implicit electron advance for this species

		.. py:function:: thermometric conductivity = k

		 	:param float k: Thermometric conductivity. Thermometric conductivity is :math:`K/\rho c_p`, where K = heat conductivity.  For air, k = 2e-5 m^2/s = 0.2 cm^2/s, and K = 2.5e-4 W/(cm*K). SPARC solves the heat equation :math:`\rho c_v dT/dt - \nabla\cdot (K \nabla T) = 0`.  For electrons the Braginskii conductivity is used.

		.. py:function:: kinematic viscosity = x

		 	:param float x: Kinematic viscosity. Kinematic viscosity is :math:`X/\rho`, where X = dynamic viscosity. For air, kinematic viscosity is about 0.15 cm^2/s. SPARC solves the momentum diffusion equation :math:`\rho dv/dt - \nabla\cdot (X \nabla v) = 0`.

		.. py:function:: effective mass = meff

		 	:param float meff: effective mass for density >> 1.0 for electrons moving through this chemical

		.. py:function:: permittivity = (epsr,epsi)

		 	:param float epsr: real part of permittivity relative to free space permittivity
		 	:param float epsi: imaginary part of permittivity relative to free space permittivity


.. py:function:: new group [<name>] [for <name>] { directives }

	Create an equilibrium group module.  This is a container for chemical species that are assumed to be in equilibrium with one another, and therefore have a common temperature and velocity.  All chemicals are part of a group.

	The ``group`` module uses automatic attachment, i.e., if created at the root level without the ``for`` clause it is automatically attached to ``hydrodynamics``. The ``hydrodynamics`` module is automatically created, if necessary.

	:param str name: name given to the group
	:param block directives: The following directives are supported:

		.. py:function:: mobile = tst

			:param bool tst: whether chemicals in this group are mobile or immobile


SPARC Collision Directives
--------------------------

SPARC collisions broadly include elastic and inelastic collisions, as well as chemical reactions.  All such processes have to explicitly resolved.  These directives are special in that they use a compact, ordered declaration (without the usual parameter block), and use dimensional numbers in CGS-eV units.  This is due to the potentially large number of such constructs that may appear in an input file.  **Dimensional numbers should not be used**.

SPARC collision directives should appear at the root level in the input file.  They find their parent modules automatically.  This makes it more straightforward to ``#include`` reaction data from separate files.

.. py:function:: new collision = sp1 <-> sp2 , cross section = sigma

	:param str sp1: name of chemical species 1 in two-body collision
	:param str sp2: name of chemical species 2 in two-body collision
	:param float sigma: cross section in square centimeters

.. py:function:: new collision = sp1 <-> sp1 , coulomb

	Uses the Coulomb collision cross section, derived from local conditions.

	:param str sp1: name of chemical species 1 in two-body collision
	:param str sp2: name of chemical species 2 in two-body collision

.. py:function:: new collision = sp1 <-> sp1 , metallic , ks = ks0 , fermi_energy_ev = ef , ref_density = nref

	Uses the harmonic mean of electron-phonon and coulomb collision rates

	:param float ks0: dimensionless, see K. Eidmann et al., Phys. Rev. E 62, 1202 (2000)
	:param float ef: the Fermi energy in eV
	:param float nref: the density at which the formula directly applies in particles per cubic centimeter

.. py:function:: new reaction = { eq1 : eq2 : eq3 : ... } rate = c0 c1 c2 cat(range)

	Sets up a chemical reaction between arbitrary species using a modified Arrhenius rate

	:math:`{\cal R} = c_0 T^{c_1} \exp(-c_2/T)`

	over a range of temperatures.  Piecewise rate constructions can be created by using multiple reactions which have the same equation but different rates and different temperature ranges.

	:param str eq1: chemical equation, or subreaction, in the form ``r1 + r2 + ... -> p1 + p2 + ... + eps``, where ``r1`` etc. are replaced by names of reactants, ``p1`` etc. are replaced by names of products, and ``eps`` is a heat of reaction in eV.  Breaking the reaction into subreactions can be used to control the flow of energy from reactants to products.  The heat of reaction, if negative, is taken from the equilibrium group of the last reactant listed.  If positive, it is added to the equilibrium group of the last product listed.

	:param float c0: rate coefficient in cm^(3(N-1))/s, where N is the number of reactants
	:param float c1: dimensionless exponent in rate law
	:param float c2: temperature reference appearing in rate law in eV
	:param str cat: name of the chemical to be considered the catalyst, i.e., the one whose temperature affects the rate
	:param numpy_range range: range of temperatures specified as in numpy, i.e., T1:T2, where T1 and T2 are floating point literals, given in eV.  Also as in numpy, :T2 means 0-T2, while T1: means T1-infinity.

.. py:function:: new reaction = { eq1 : eq2 : eq3 : ... } janev_rate = c0 c1 c2 c3 c4 c5 c6 c7 c8 cat(range)

	Alternative way of specifying the reaction rate:

		:math:`\ln {\cal R} = \sum_{n=0}^{8} c_n (\ln T)^n`

.. py:function:: new excitation = sp1 -> sp2 level = n rate = c0 c1 c2

	Vibrational excitation of one species by another.  If level = n the transition is between ground and level n.  If level = 0 the transition is between adjacent levels, where it is assumed the rate for transitions from n to n+1 is the same for all n.

.. py:function:: new excitation = sp1 -> sp2 level = n janev_rate = c0 c1 c2 c3 c4 c5 c6 c7 c8

	Alternative way of specifying the excitation rate.
