{
	volScalarField kappa1
    (
        IOobject("kappa1", runTime.timeName(), mesh, IOobject::NO_READ, IOobject::NO_WRITE),
        kappa 
    );

    volScalarField cp1
    (
        IOobject("cp1", runTime.timeName(), mesh, IOobject::NO_READ, IOobject::NO_WRITE),
        cp
    );

	forAll(kappa, celli)
	{
		kappa1[celli] = kappaPtr->value(T[celli]) * epsilon1[celli] + kappasPtr->value(T[celli]) * (1.0 - epsilon1[celli]);
		kappa[celli] = alpha1[celli] * kappa1[celli] + (1.0 - alpha1[celli]) * kappa2l.value();

		cp1[celli] = cpPtr->value(T[celli]) * epsilon1[celli] + cpsPtr->value(T[celli]) * (1.0 - epsilon1[celli]);
		cp[celli] = alpha1[celli] * cp1[celli] + (1.0 - alpha1[celli]) * Cp2l.value();

	}

/*
	forAll(kappa, celli)
	{
		kappa1[celli] = polykappa1l.value(T[celli]) * epsilon1[celli] + polykappa1s.value(T[celli]) * (1.0 - epsilon1[celli]);
		kappa[celli] = alpha1[celli] * kappa1[celli] + (1.0 - alpha1[celli]) * kappa2l.value();

		cp1[celli] = polycp1l.value(T[celli]) * epsilon1[celli] + polycp1s.value(T[celli]) * (1.0 - epsilon1[celli]);
		cp[celli] = alpha1[celli] * cp1[celli] + (1.0 - alpha1[celli]) * Cp2l.value();
	}
*/

/*
	volScalarField kappa1 = kappa1l * epsilon1 + kappa1s * (1.0 - epsilon1);
	kappa = alpha1 * kappa1 + (1.0 - alpha1) * kappa2l;

	volScalarField Cp1 = Cp1l * epsilon1 + Cp1s * (1.0 - epsilon1);
	cp = alpha1 * Cp1 + (1.0 - alpha1) * Cp2l;
*/

	// kappa print
    Info << "av kappa = "
         << kappa.weightedAverage(mesh.Vsc()).value()
         << "  | max kappa = "
         << gMax(kappa.internalField())
		 << "  | min kappa = "
         << gMin(kappa.internalField()) << endl;
	
    // cp print
    Info << "av cp = "
         << cp.weightedAverage(mesh.Vsc()).value()
         << "  | max cp = "
         << gMax(cp.internalField())
 		 << "  | min cp = "
         << gMin(cp.internalField()) << endl;

    kappa.correctBoundaryConditions();
    cp.correctBoundaryConditions();
}
