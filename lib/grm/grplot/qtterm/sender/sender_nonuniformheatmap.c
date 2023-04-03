#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "grm.h"

static double x[41] = {-2.,         -1.8974359,  -1.79487179, -1.69230769, -1.58974359, -1.48717949, -1.38461538,
                       -1.28205128, -1.17948718, -1.07692308, -0.97435897, -0.87179487, -0.76923077, -0.66666667,
                       -0.56410256, -0.46153846, -0.35897436, -0.25641026, -0.15384615, -0.05128205, 0.05128205,
                       0.15384615,  0.25641026,  0.35897436,  0.46153846,  0.56410256,  0.66666667,  0.76923077,
                       0.87179487,  0.97435897,  1.07692308,  1.17948718,  1.28205128,  1.38461538,  1.48717949,
                       1.58974359,  1.69230769,  1.79487179,  1.8974359,   2.,          3.};
static double y[21] = {0.,         0.16534698, 0.33069396, 0.49604095, 0.66138793, 0.82673491, 0.99208189,
                       1.15742887, 1.32277585, 1.48812284, 1.65346982, 1.8188168,  1.98416378, 2.14951076,
                       2.31485774, 2.48020473, 2.64555171, 2.81089869, 2.97624567, 3.14159265, 4.};
static double z[20][40] = {
    {-1.90929743e+00, -1.94712592e+00, -1.97499996e+00, -1.99262657e+00, -1.99982051e+00, -1.99650615e+00,
     -1.98271834e+00, -1.95860198e+00, -1.92441054e+00, -1.88050339e+00, -1.82734200e+00, -1.76548509e+00,
     -1.69558279e+00, -1.61836980e+00, -1.53465764e+00, -1.44532612e+00, -1.35131415e+00, -1.25360981e+00,
     -1.15323998e+00, -1.05125958e+00, -9.48740423e-01, -8.46760017e-01, -7.46390189e-01, -6.48685846e-01,
     -5.54673877e-01, -4.65342364e-01, -3.81630197e-01, -3.04417206e-01, -2.34514914e-01, -1.72658005e-01,
     -1.19496607e-01, -7.55894552e-02, -4.13980219e-02, -1.72816650e-02, -3.49385154e-03, -1.79494017e-04,
     -7.37342688e-03, -2.50000406e-02, -5.28740764e-02, -9.07025732e-02},
    {-1.89565873e+00, -1.93348723e+00, -1.96136126e+00, -1.97898788e+00, -1.98618181e+00, -1.98286745e+00,
     -1.96907964e+00, -1.94496328e+00, -1.91077185e+00, -1.86686470e+00, -1.81370330e+00, -1.75184639e+00,
     -1.68194410e+00, -1.60473111e+00, -1.52101894e+00, -1.43168743e+00, -1.33767546e+00, -1.23997111e+00,
     -1.13960129e+00, -1.03762088e+00, -9.35101727e-01, -8.33121320e-01, -7.32751493e-01, -6.35047149e-01,
     -5.41035180e-01, -4.51703667e-01, -3.67991500e-01, -2.90778510e-01, -2.20876217e-01, -1.59019308e-01,
     -1.05857910e-01, -6.19507586e-02, -2.77593253e-02, -3.64296836e-03, 1.01448451e-02,  1.34592026e-02,
     6.26526972e-03,  -1.13613440e-02, -3.92353798e-02, -7.70638766e-02},
    {-1.85511467e+00, -1.89294317e+00, -1.92081720e+00, -1.93844381e+00, -1.94563775e+00, -1.94232339e+00,
     -1.92853558e+00, -1.90441922e+00, -1.87022779e+00, -1.82632063e+00, -1.77315924e+00, -1.71130233e+00,
     -1.64140004e+00, -1.56418704e+00, -1.48047488e+00, -1.39114337e+00, -1.29713140e+00, -1.19942705e+00,
     -1.09905723e+00, -9.97076819e-01, -8.94557665e-01, -7.92577258e-01, -6.92207431e-01, -5.94503088e-01,
     -5.00491118e-01, -4.11159605e-01, -3.27447439e-01, -2.50234448e-01, -1.80332155e-01, -1.18475247e-01,
     -6.53138486e-02, -2.14066969e-02, 1.27847364e-02,  3.69010933e-02,  5.06889068e-02,  5.40032643e-02,
     4.68093314e-02,  2.91827177e-02,  1.30868190e-03,  -3.65198149e-02},
    {-1.78877118e+00, -1.82659967e+00, -1.85447371e+00, -1.87210032e+00, -1.87929426e+00, -1.87597990e+00,
     -1.86219209e+00, -1.83807573e+00, -1.80388430e+00, -1.75997714e+00, -1.70681575e+00, -1.64495884e+00,
     -1.57505654e+00, -1.49784355e+00, -1.41413139e+00, -1.32479987e+00, -1.23078791e+00, -1.13308356e+00,
     -1.03271373e+00, -9.30733328e-01, -8.28214174e-01, -7.26233768e-01, -6.25863940e-01, -5.28159597e-01,
     -4.34147628e-01, -3.44816115e-01, -2.61103948e-01, -1.83890957e-01, -1.13988665e-01, -5.21317562e-02,
     1.02964190e-03,  4.49367936e-02,  7.91282269e-02,  1.03244584e-01,  1.17032397e-01,  1.20346755e-01,
     1.13152822e-01,  9.55262082e-02,  6.76521724e-02,  2.98236756e-02},
    {-1.69843794e+00, -1.73626643e+00, -1.76414047e+00, -1.78176708e+00, -1.78896102e+00, -1.78564666e+00,
     -1.77185884e+00, -1.74774249e+00, -1.71355105e+00, -1.66964390e+00, -1.61648250e+00, -1.55462560e+00,
     -1.48472330e+00, -1.40751031e+00, -1.32379815e+00, -1.23446663e+00, -1.14045466e+00, -1.04275032e+00,
     -9.42380493e-01, -8.40400086e-01, -7.37880932e-01, -6.35900526e-01, -5.35530699e-01, -4.37826355e-01,
     -3.43814386e-01, -2.54482873e-01, -1.70770706e-01, -9.35577156e-02, -2.36554232e-02, 3.82014856e-02,
     9.13628837e-02,  1.35270035e-01,  1.69461469e-01,  1.93577826e-01,  2.07365639e-01,  2.10679997e-01,
     2.03486064e-01,  1.85859450e-01,  1.57985414e-01,  1.20156917e-01},
    {-1.58657900e+00, -1.62440750e+00, -1.65228153e+00, -1.66990814e+00, -1.67710208e+00, -1.67378772e+00,
     -1.65999991e+00, -1.63588355e+00, -1.60169212e+00, -1.55778496e+00, -1.50462357e+00, -1.44276666e+00,
     -1.37286437e+00, -1.29565137e+00, -1.21193921e+00, -1.12260769e+00, -1.02859573e+00, -9.30891382e-01,
     -8.30521555e-01, -7.28541149e-01, -6.26021995e-01, -5.24041588e-01, -4.23671761e-01, -3.25967418e-01,
     -2.31955448e-01, -1.42623935e-01, -5.89117686e-02, 1.83012221e-02,  8.82035146e-02,  1.50060423e-01,
     2.03221821e-01,  2.47128973e-01,  2.81320406e-01,  3.05436763e-01,  3.19224577e-01,  3.22538934e-01,
     3.15345001e-01,  2.97718388e-01,  2.69844352e-01,  2.32015855e-01},
    {-1.45624558e+00, -1.49407408e+00, -1.52194812e+00, -1.53957473e+00, -1.54676866e+00, -1.54345431e+00,
     -1.52966649e+00, -1.50555014e+00, -1.47135870e+00, -1.42745155e+00, -1.37429015e+00, -1.31243324e+00,
     -1.24253095e+00, -1.16531796e+00, -1.08160579e+00, -9.92274281e-01, -8.98262312e-01, -8.00557969e-01,
     -7.00188142e-01, -5.98207735e-01, -4.95688581e-01, -3.93708175e-01, -2.93338347e-01, -1.95634004e-01,
     -1.01622035e-01, -1.22905217e-02, 7.14216449e-02,  1.48634636e-01,  2.18536928e-01,  2.80393837e-01,
     3.33555235e-01,  3.77462387e-01,  4.11653820e-01,  4.35770177e-01,  4.49557990e-01,  4.52872348e-01,
     4.45678415e-01,  4.28051801e-01,  4.00177765e-01,  3.62349269e-01},
    {-1.31099285e+00, -1.34882135e+00, -1.37669538e+00, -1.39432200e+00, -1.40151593e+00, -1.39820157e+00,
     -1.38441376e+00, -1.36029740e+00, -1.32610597e+00, -1.28219882e+00, -1.22903742e+00, -1.16718051e+00,
     -1.09727822e+00, -1.02006523e+00, -9.36353061e-01, -8.47021548e-01, -7.53009579e-01, -6.55305235e-01,
     -5.54935408e-01, -4.52955002e-01, -3.50435848e-01, -2.48455441e-01, -1.48085614e-01, -5.03812707e-02,
     4.36306987e-02,  1.32962212e-01,  2.16674378e-01,  2.93887369e-01,  3.63789662e-01,  4.25646570e-01,
     4.78807968e-01,  5.22715120e-01,  5.56906553e-01,  5.81022910e-01,  5.94810724e-01,  5.98125081e-01,
     5.90931148e-01,  5.73304535e-01,  5.45430499e-01,  5.07602002e-01},
    {-1.15478291e+00, -1.19261141e+00, -1.22048545e+00, -1.23811206e+00, -1.24530599e+00, -1.24199164e+00,
     -1.22820382e+00, -1.20408747e+00, -1.16989603e+00, -1.12598888e+00, -1.07282748e+00, -1.01097057e+00,
     -9.41068281e-01, -8.63855290e-01, -7.80143124e-01, -6.90811610e-01, -5.96799641e-01, -4.99095298e-01,
     -3.98725471e-01, -2.96745064e-01, -1.94225910e-01, -9.22455037e-02, 8.12432357e-03,  1.05828667e-01,
     1.99840636e-01,  2.89172149e-01,  3.72884316e-01,  4.50097307e-01,  5.19999599e-01,  5.81856508e-01,
     6.35017906e-01,  6.78925058e-01,  7.13116491e-01,  7.37232848e-01,  7.51020661e-01,  7.54335019e-01,
     7.47141086e-01,  7.29514472e-01,  7.01640436e-01,  6.63811940e-01},
    {-9.91876772e-01, -1.02970527e+00, -1.05757930e+00, -1.07520592e+00, -1.08239985e+00, -1.07908549e+00,
     -1.06529768e+00, -1.04118132e+00, -1.00698989e+00, -9.63082739e-01, -9.09921340e-01, -8.48064432e-01,
     -7.78162139e-01, -7.00949149e-01, -6.17236982e-01, -5.27905469e-01, -4.33893499e-01, -3.36189156e-01,
     -2.35819329e-01, -1.33838922e-01, -3.13197686e-02, 7.06606380e-02,  1.71030465e-01,  2.68734809e-01,
     3.62746778e-01,  4.52078291e-01,  5.35790458e-01,  6.13003448e-01,  6.82905741e-01,  7.44762650e-01,
     7.97924048e-01,  8.41831199e-01,  8.76022633e-01,  9.00138990e-01,  9.13926803e-01,  9.17241161e-01,
     9.10047228e-01,  8.92420614e-01,  8.64546578e-01,  8.26718081e-01},
    {-8.26718081e-01, -8.64546578e-01, -8.92420614e-01, -9.10047228e-01, -9.17241161e-01, -9.13926803e-01,
     -9.00138990e-01, -8.76022633e-01, -8.41831199e-01, -7.97924048e-01, -7.44762650e-01, -6.82905741e-01,
     -6.13003448e-01, -5.35790458e-01, -4.52078291e-01, -3.62746778e-01, -2.68734809e-01, -1.71030465e-01,
     -7.06606380e-02, 3.13197686e-02,  1.33838922e-01,  2.35819329e-01,  3.36189156e-01,  4.33893499e-01,
     5.27905469e-01,  6.17236982e-01,  7.00949149e-01,  7.78162139e-01,  8.48064432e-01,  9.09921340e-01,
     9.63082739e-01,  1.00698989e+00,  1.04118132e+00,  1.06529768e+00,  1.07908549e+00,  1.08239985e+00,
     1.07520592e+00,  1.05757930e+00,  1.02970527e+00,  9.91876772e-01},
    {-6.63811940e-01, -7.01640436e-01, -7.29514472e-01, -7.47141086e-01, -7.54335019e-01, -7.51020661e-01,
     -7.37232848e-01, -7.13116491e-01, -6.78925058e-01, -6.35017906e-01, -5.81856508e-01, -5.19999599e-01,
     -4.50097307e-01, -3.72884316e-01, -2.89172149e-01, -1.99840636e-01, -1.05828667e-01, -8.12432357e-03,
     9.22455037e-02,  1.94225910e-01,  2.96745064e-01,  3.98725471e-01,  4.99095298e-01,  5.96799641e-01,
     6.90811610e-01,  7.80143124e-01,  8.63855290e-01,  9.41068281e-01,  1.01097057e+00,  1.07282748e+00,
     1.12598888e+00,  1.16989603e+00,  1.20408747e+00,  1.22820382e+00,  1.24199164e+00,  1.24530599e+00,
     1.23811206e+00,  1.22048545e+00,  1.19261141e+00,  1.15478291e+00},
    {-5.07602002e-01, -5.45430499e-01, -5.73304535e-01, -5.90931148e-01, -5.98125081e-01, -5.94810724e-01,
     -5.81022910e-01, -5.56906553e-01, -5.22715120e-01, -4.78807968e-01, -4.25646570e-01, -3.63789662e-01,
     -2.93887369e-01, -2.16674378e-01, -1.32962212e-01, -4.36306987e-02, 5.03812707e-02,  1.48085614e-01,
     2.48455441e-01,  3.50435848e-01,  4.52955002e-01,  5.54935408e-01,  6.55305235e-01,  7.53009579e-01,
     8.47021548e-01,  9.36353061e-01,  1.02006523e+00,  1.09727822e+00,  1.16718051e+00,  1.22903742e+00,
     1.28219882e+00,  1.32610597e+00,  1.36029740e+00,  1.38441376e+00,  1.39820157e+00,  1.40151593e+00,
     1.39432200e+00,  1.37669538e+00,  1.34882135e+00,  1.31099285e+00},
    {-3.62349269e-01, -4.00177765e-01, -4.28051801e-01, -4.45678415e-01, -4.52872348e-01, -4.49557990e-01,
     -4.35770177e-01, -4.11653820e-01, -3.77462387e-01, -3.33555235e-01, -2.80393837e-01, -2.18536928e-01,
     -1.48634636e-01, -7.14216449e-02, 1.22905217e-02,  1.01622035e-01,  1.95634004e-01,  2.93338347e-01,
     3.93708175e-01,  4.95688581e-01,  5.98207735e-01,  7.00188142e-01,  8.00557969e-01,  8.98262312e-01,
     9.92274281e-01,  1.08160579e+00,  1.16531796e+00,  1.24253095e+00,  1.31243324e+00,  1.37429015e+00,
     1.42745155e+00,  1.47135870e+00,  1.50555014e+00,  1.52966649e+00,  1.54345431e+00,  1.54676866e+00,
     1.53957473e+00,  1.52194812e+00,  1.49407408e+00,  1.45624558e+00},
    {-2.32015855e-01, -2.69844352e-01, -2.97718388e-01, -3.15345001e-01, -3.22538934e-01, -3.19224577e-01,
     -3.05436763e-01, -2.81320406e-01, -2.47128973e-01, -2.03221821e-01, -1.50060423e-01, -8.82035146e-02,
     -1.83012221e-02, 5.89117686e-02,  1.42623935e-01,  2.31955448e-01,  3.25967418e-01,  4.23671761e-01,
     5.24041588e-01,  6.26021995e-01,  7.28541149e-01,  8.30521555e-01,  9.30891382e-01,  1.02859573e+00,
     1.12260769e+00,  1.21193921e+00,  1.29565137e+00,  1.37286437e+00,  1.44276666e+00,  1.50462357e+00,
     1.55778496e+00,  1.60169212e+00,  1.63588355e+00,  1.65999991e+00,  1.67378772e+00,  1.67710208e+00,
     1.66990814e+00,  1.65228153e+00,  1.62440750e+00,  1.58657900e+00},
    {-1.20156917e-01, -1.57985414e-01, -1.85859450e-01, -2.03486064e-01, -2.10679997e-01, -2.07365639e-01,
     -1.93577826e-01, -1.69461469e-01, -1.35270035e-01, -9.13628837e-02, -3.82014856e-02, 2.36554232e-02,
     9.35577156e-02,  1.70770706e-01,  2.54482873e-01,  3.43814386e-01,  4.37826355e-01,  5.35530699e-01,
     6.35900526e-01,  7.37880932e-01,  8.40400086e-01,  9.42380493e-01,  1.04275032e+00,  1.14045466e+00,
     1.23446663e+00,  1.32379815e+00,  1.40751031e+00,  1.48472330e+00,  1.55462560e+00,  1.61648250e+00,
     1.66964390e+00,  1.71355105e+00,  1.74774249e+00,  1.77185884e+00,  1.78564666e+00,  1.78896102e+00,
     1.78176708e+00,  1.76414047e+00,  1.73626643e+00,  1.69843794e+00},
    {-2.98236756e-02, -6.76521724e-02, -9.55262082e-02, -1.13152822e-01, -1.20346755e-01, -1.17032397e-01,
     -1.03244584e-01, -7.91282269e-02, -4.49367936e-02, -1.02964190e-03, 5.21317562e-02,  1.13988665e-01,
     1.83890957e-01,  2.61103948e-01,  3.44816115e-01,  4.34147628e-01,  5.28159597e-01,  6.25863940e-01,
     7.26233768e-01,  8.28214174e-01,  9.30733328e-01,  1.03271373e+00,  1.13308356e+00,  1.23078791e+00,
     1.32479987e+00,  1.41413139e+00,  1.49784355e+00,  1.57505654e+00,  1.64495884e+00,  1.70681575e+00,
     1.75997714e+00,  1.80388430e+00,  1.83807573e+00,  1.86219209e+00,  1.87597990e+00,  1.87929426e+00,
     1.87210032e+00,  1.85447371e+00,  1.82659967e+00,  1.78877118e+00},
    {3.65198149e-02,  -1.30868190e-03, -2.91827177e-02, -4.68093314e-02, -5.40032643e-02, -5.06889068e-02,
     -3.69010933e-02, -1.27847364e-02, 2.14066969e-02,  6.53138486e-02,  1.18475247e-01,  1.80332155e-01,
     2.50234448e-01,  3.27447439e-01,  4.11159605e-01,  5.00491118e-01,  5.94503088e-01,  6.92207431e-01,
     7.92577258e-01,  8.94557665e-01,  9.97076819e-01,  1.09905723e+00,  1.19942705e+00,  1.29713140e+00,
     1.39114337e+00,  1.48047488e+00,  1.56418704e+00,  1.64140004e+00,  1.71130233e+00,  1.77315924e+00,
     1.82632063e+00,  1.87022779e+00,  1.90441922e+00,  1.92853558e+00,  1.94232339e+00,  1.94563775e+00,
     1.93844381e+00,  1.92081720e+00,  1.89294317e+00,  1.85511467e+00},
    {7.70638766e-02, 3.92353798e-02, 1.13613440e-02, -6.26526972e-03, -1.34592026e-02, -1.01448451e-02, 3.64296836e-03,
     2.77593253e-02, 6.19507586e-02, 1.05857910e-01, 1.59019308e-01,  2.20876217e-01,  2.90778510e-01,  3.67991500e-01,
     4.51703667e-01, 5.41035180e-01, 6.35047149e-01, 7.32751493e-01,  8.33121320e-01,  9.35101727e-01,  1.03762088e+00,
     1.13960129e+00, 1.23997111e+00, 1.33767546e+00, 1.43168743e+00,  1.52101894e+00,  1.60473111e+00,  1.68194410e+00,
     1.75184639e+00, 1.81370330e+00, 1.86686470e+00, 1.91077185e+00,  1.94496328e+00,  1.96907964e+00,  1.98286745e+00,
     1.98618181e+00, 1.97898788e+00, 1.96136126e+00, 1.93348723e+00,  1.89565873e+00},
    {9.07025732e-02, 5.28740764e-02, 2.50000406e-02, 7.37342688e-03, 1.79494017e-04, 3.49385154e-03, 1.72816650e-02,
     4.13980219e-02, 7.55894552e-02, 1.19496607e-01, 1.72658005e-01, 2.34514914e-01, 3.04417206e-01, 3.81630197e-01,
     4.65342364e-01, 5.54673877e-01, 6.48685846e-01, 7.46390189e-01, 8.46760017e-01, 9.48740423e-01, 1.05125958e+00,
     1.15323998e+00, 1.25360981e+00, 1.35131415e+00, 1.44532612e+00, 1.53465764e+00, 1.61836980e+00, 1.69558279e+00,
     1.76548509e+00, 1.82734200e+00, 1.88050339e+00, 1.92441054e+00, 1.95860198e+00, 1.98271834e+00, 1.99650615e+00,
     1.99982051e+00, 1.99262657e+00, 1.97499996e+00, 1.94712592e+00, 1.90929743e+00}};

int test_sendmeta_ref(void)
{
  void *handle;

  printf("sending data...");
  fflush(stdout);

  handle = grm_open(GRM_SENDER, "localhost", 8002, NULL, NULL);
  if (handle == NULL)
    {
      fprintf(stderr, "sender could not be created\n");
      return 1;
    }
  double xlim[2] = {-2, 3.};
  double ylim[2] = {0, 4.};
  double zlim[2] = {-2, 2};
  grm_send_ref(handle, "series", 'O', "[", 0);
  grm_send_ref(handle, "x", 'D', x, 41);
  grm_send_ref(handle, "y", 'D', y, 21);
  grm_send_ref(handle, "z", 'D', z, 20 * 40);
  grm_send_ref(handle, NULL, 'O', "]", 0);
  grm_send_ref(handle, "kind", 's', "nonuniformheatmap", 0);
  grm_send_ref(handle, "xlim", 'D', xlim, 2);
  grm_send_ref(handle, "ylim", 'D', ylim, 2);
  grm_send_ref(handle, "zlim", 'D', zlim, 2);
  grm_send_ref(handle, NULL, '\0', NULL, 0);

  printf("\tsent\n");

  grm_close(handle);
  grm_finalize();
  return 0;
}


int main(void)
{
  return test_sendmeta_ref();
}
