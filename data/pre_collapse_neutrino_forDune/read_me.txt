1.total_nue::electron-type neutrino
  spe_all*.dat::spectrum
    * descirbes the time step. Please see the data file of luminosity.
    neutrino energy [MeV], number[cm^-3MeV^-1s^-1]

  total_nue_all.dat::luminosity
    time to collapse [s], number luminosity [cm^-3s^-1], energy luminosity [MeV/cm^3/s], time step

2.total_nueb::electron-type anti-neutrino
  spe_all*.dat::spectrum
    * descirbes the time step. Please see the rho_t_center.dat
    neutrino energy [MeV], number[cm^-3MeV^-1s^-1]

  total_nue_all.dat::luminosity
    time to collapse [s], number luminosity [cm^-3s^-1], energy luminosity [MeV/cm^3/s], time step      


3.total_nux::heavy lepton-type neutrino
  spe_sum_mu* :: mu- or tau-type anti-neutrino (nux_b)
  spe_sum_mu_nu* :: mu- or tau-type neutrino (nux)
    neutrino energy [MeV], number[cm^-3MeV^-1s^-1]
  
  lightcurve.dat :: luminosity
    time step, time to collapse[s], *, *, energy luminosity of nux_b[Mev/cm^3/s], number luminosity of nux or nux_b[MeV/cm^3/s], *, energy luminosity of nux[MeV/cm^3/s]. *
  please neglect the arrays described as "*".
 
  In this data, we assume that mu- and tau-type neutrinos have the same spectra and luminosities.

4.step.dat
  In this file, we write the time step used in our calculations.
