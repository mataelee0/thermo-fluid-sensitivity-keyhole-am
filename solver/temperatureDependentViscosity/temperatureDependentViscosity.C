#include "temperatureDependentViscosity.H"
#include "addToRunTimeSelectionTable.H"
#include "fvCFD.H"

namespace Foam {
namespace viscosityModels {

// Register into the viscosityModel run-time selection table
defineTypeNameAndDebug(temperatureDependentViscosity, 0);
addToRunTimeSelectionTable
(
    viscosityModel,
    temperatureDependentViscosity,
    dictionary
);

} // namespace viscosityModels
} // namespace Foam

using namespace Foam;
using namespace Foam::viscosityModels;


// * * * * * * * * * * * * *  Constructor  * * * * * * * * * * * * * * * * * //

temperatureDependentViscosity::temperatureDependentViscosity
(
    const fvMesh& mesh,
    const word& group
)
:
    // Base builds dictionary context for this model scope
    viscosityModel(mesh, group),

    // Temperature field name (default "T") and field reference
    TName_( this->lookupOrDefault<word>("TName", "T") ),
    T_
    (
        mesh.lookupObject<volScalarField>(TName_)
    ),

    // Allocate kinematic viscosity field (group-aware object name)
    nu_
    (
        IOobject
        (
            IOobject::groupName("nu", group),
            mesh.time().timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionedScalar("zero", dimViscosity, 0.0)
    )
{
    // Read the nu Function1 under key "nu"
    // e.g.  nu  nu [0 2 -1 0 0 0 0] table ( ... );
    nuFun_.reset( Function1<scalar>::New("nu", *this).ptr() );

    // Initial evaluation
    correct();
}


// * * * * * * * * * * * * *  Member Functions  * * * * * * * * * * * * * * //

void temperatureDependentViscosity::correct()
{
    // Update internal field: nu[i] = nuFun(T[i])
    scalarField& nuIF = nu_.primitiveFieldRef();
    const scalarField& TIF = T_.internalField();

    forAll(TIF, i)
    {
        nuIF[i] = nuFun_->value(TIF[i]);
    }

    // Let BCs adjust consistently
    nu_.correctBoundaryConditions();
}


bool temperatureDependentViscosity::read()
{
    // Re-read parent coefficients (keeps dictionary/group in sync)
    if (!viscosityModel::read())
    {
        return false;
    }

    // Update TName if provided
    TName_ = this->lookupOrDefault<word>("TName", TName_);

    // Rebuild Function1 in case coefficients changed
    nuFun_.reset( Function1<scalar>::New("nu", *this).ptr() );

    // Refresh field
    correct();
    return true;
}

