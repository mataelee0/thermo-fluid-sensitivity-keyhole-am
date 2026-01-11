    // 9. alpha1, epsilon1 -> find depth
    const vectorField& cellC = mesh.C();

    label nIntF = mesh.nInternalFaces();
    
    depth_y *= 0.0;
    melt_depth_y *= 0.0;
            
    for (label faceI = 0; faceI < nIntF; ++faceI)
    {   
        label own = mesh.owner()[faceI];
        label nei = mesh.neighbour()[faceI];
        
        scalar cOwn = alpha1[own];
        scalar cNei = alpha1[nei];
            
        scalar eOwn = epsilon1[own]; 
        scalar eNei = epsilon1[nei];

            
        if ((cOwn - 0.5) * (cNei - 0.5) < 0)
        {       
            scalar yOwn = cellC[own].y();
            scalar yNei = cellC[nei].y();

            //std::cout << faceI << " " << own << " " << nei << " " << cOwn << " " << cNei << " " << yOwn << " " << yNei << std::endl;
            scalar alpha_con = (0.5 - cOwn) / (cNei - cOwn);
            
            scalar yInt = yOwn + alpha_con * (yNei - yOwn);
            if (depth_y[own] < yInt)
                depth_y[own] = yInt;
        }
            
        if ((eOwn - 0.5) * (eNei - 0.5) < 0)
        {   
            scalar yOwn = cellC[own].y();
            scalar yNei = cellC[nei].y();
            
            //std::cout << faceI << " " << own << " " << nei << " " << cOwn << " " << cNei << " " << yOwn << " " << yNei << std::endl;
            scalar alpha_con = (0.5 - eOwn) / (eNei - eOwn);
            
            scalar yInt = yOwn + alpha_con * (yNei - yOwn);
            if (melt_depth_y[own] < yInt)
                melt_depth_y[own] = yInt;
        }           
                
    }
    scalar globalMaxY = gMax(depth_y.internalField());
    scalar globalMaxMeltY = gMax(melt_depth_y.internalField());
    scalar y_ini = 1e-4;
    Info << "keyhole depth: " << globalMaxY - y_ini << endl;
    Info << "melt depth: " << globalMaxMeltY - y_ini << endl;
