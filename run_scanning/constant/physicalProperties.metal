/*--------------------------------*- C++ -*----------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Version:  10
     \\/     M anipulation  |
\*---------------------------------------------------------------------------*/
FoamFile
{
    format      ascii;
    class       dictionary;
    location    "constant";
    object      physicalProperties.water;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

viscosityModel  temperatureDependentViscosity;

nu table
(
    (1923 9.96725E-07)
    (2387 5.09269E-07)
    (2851 3.30349E-07)
    (3315 2.46497E-07)
);

rho 4086.65;

kappa table
(
    (1923.00 28.70)
    (2317.43 35.61)
    (3315.00 45.15)
);

kappas table
(  
    (291.70 6.78)
    (1276.52 19.14)
    (1873.00 26.82)
);


cp table
(   
    (1923 831.00)
    (3315 702.96)
);

cps table
(  
    (296.31474 588.77)
    (1269.30967 788.91)
    (1274.5248 670.13)
    (1873 769.26) 
);
    
Tsolidus 1873.0;
Tliquidus 1923.0;
LatentHeat 285000;
beta 0.0000089;

elec_resistivity 1.66e-6;

// ************************************************************************* //
