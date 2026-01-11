#ifndef temperatureDependentViscosity_H
#define temperatureDependentViscosity_H

#include "viscosityModel.H"
#include "Function1.H"
#include "volFields.H"

namespace Foam {
namespace viscosityModels {

/*---------------------------------------------------------------------------*\
  Class: temperatureDependentViscosity
  Inherits: viscosityModel

  Purpose
    Temperature-dependent molecular kinematic viscosity:
      nu = nu(T)

    The temperature dependence is provided via a Function1<scalar> read from
    the model dictionary under the key "nu". Any Function1 type is supported
    (table, polynomial, coded, ...).

  Dictionary usage (in the same scope this model reads from):
    viscosityModel  temperatureDependentViscosity;

    // Optional; defaults to "T"
    TName           T;

    // Kinematic viscosity as Function1
    // [0 2 -1 0 0 0 0] = m^2/s
    nu  nu [0 2 -1 0 0 0 0] table
    (
        (0      1.00e-06)   // guard (min)
        (300    1.10e-06)
        (1500   2.50e-06)
        (4000   6.00e-06)
        (10000  6.00e-06)   // guard (max)
    );
\*---------------------------------------------------------------------------*/

class temperatureDependentViscosity : public viscosityModel
{
    //- nu(T) as a runtime-selectable Function1
    autoPtr<Function1<scalar>> nuFun_;

    //- Temperature field name and reference (defaults to "T")
    word TName_;
    const volScalarField& T_;

    //- Cell-wise molecular kinematic viscosity [m^2/s]
    volScalarField nu_;

public:

    //- Runtime type information (selection name)
    TypeName("temperatureDependentViscosity");

    //- Construct from mesh and group (keeps parity with your current base)
    temperatureDependentViscosity(const fvMesh& mesh, const word& group);

    virtual ~temperatureDependentViscosity() {}

    //- Return molecular viscosity as a volume field
    virtual tmp<volScalarField> nu() const { return nu_; }

    //- Return molecular viscosity on a boundary patch
    virtual tmp<scalarField> nu(const label patchi) const
    {
        return nu_.boundaryField()[patchi];
    }

    //- Update cell-wise nu from the current temperature field
    virtual void correct();

    //- Read and update coefficients (Function1 and TName)
    virtual bool read();
};

} // namespace viscosityModels
} // namespace Foam

#endif

