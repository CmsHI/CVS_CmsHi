// Different Fit functions
// Use as follows:
// TF1 *fitFunction = new TF1("fitFunction", RBWPol2, 0, 200, 6);
// histMass->Fit("fitFunction","Q0","MER", 20, 120);


// Relativitic BreitWignor + BKG

Double_t RBW(Double_t *x, Double_t *par)
{
  Double_t rbw = par[0]*x[0]*par[1]*par[2]*0.5/TMath::Pi()/TMath::Max(1.e-10,(x[0]*x[0]-par[1]*par[1]) * (x[0]*x[0]-par[1]*par[1])+par[1]*par[1]*par[2]*par[2]);
  return rbw;
}

Double_t RBWPol2(Double_t *x, Double_t *par)
{
  return RBW(x,par) + Pol2(x,&par[3]);
}


Double_t RBWPol3(Double_t *x, Double_t *par)
{
  return RBW(x,par) + Pol3(x,&par[3]);
}

Double_t RBWPol4(Double_t *x, Double_t *par)
{
  return RBW(x,par) + Pol4(x,&par[3]);
}

Double_t RBWExp(Double_t *x, Double_t *par)
{
  return RBW(x,par) + Exp(x,&par[3]);

} 



// Non Relativitic BreitWignor + BKG

Double_t BW(Double_t *x, Double_t *par)
{
  Double_t rbw = par[0]*par[2]/TMath::Max(1.e-10,(x[0]*x[0]-par[1]*par[1]) * (x[0]*x[0]-par[1]*par[1]) + 0.25*par[2]*par[2]);
  return rbw;
}

Double_t BWPol2(Double_t *x, Double_t *par)
{
  return BW(x,par) + Pol2(x,&par[3]);
}


Double_t BWPol3(Double_t *x, Double_t *par)
{
  return BW(x,par) + Pol3(x,&par[3]);
}

Double_t BWPol4(Double_t *x, Double_t *par)
{
  return BW(x,par) + Pol4(x,&par[3]);
}

Double_t BWExp(Double_t *x, Double_t *par)
{
  return BW(x,par) + Exp(x,&par[3]);

} 



// Gaussians + BKG

Double_t Gaus(Double_t *x, Double_t *par)
{
  Double_t arg = 0;
  if (par[2]) arg = (x[0] - par[1])/par[2];
  Double_t gau = par[0]*TMath::Exp(-0.5*arg*arg);
  return gau;
}

Double_t GausPol2(Double_t *x, Double_t *par) 
{
  return Gaus(x,par) + Pol2(x,&par[3]);
}

Double_t GausPol3(Double_t *x, Double_t *par) 
{
  return Gaus(x,par) + Pol3(x,&par[3]);
}

Double_t GausPol4(Double_t *x, Double_t *par) 
{
  return Gaus(x,par) + Pol4(x,&par[3]);
}

Double_t GausExp(Double_t *x, Double_t *par) 
{
  return Gaus(x,par) + Exp(x,&par[3]);
}


// Polynomials

Double_t Pol1(Double_t *x, Double_t *par)
{
  Double_t pol = par[0] + par[1]*x[0];
  return pol;
}

Double_t Pol2(Double_t *x, Double_t *par)
{
  Double_t pol = par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
  return pol;
}

Double_t Pol3(Double_t *x, Double_t *par)
{
  Double_t pol = par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0];
  return pol;
}

Double_t Pol4(Double_t *x, Double_t *par)
{
  Double_t pol = par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0] + par[4]*x[0]*x[0]*x[0]*x[0];
  return pol;
}

// Exponential

Double_t Exp(Double_t *x, Double_t *par)
{
  Double_t exp = par[0] * TMath::Exp(par[1]*x[0]);
  return exp;
}



