
double deltaPhi(double phi1, double phi2) {
    double dePhi = phi1 - phi2;
    if (dePhi > 3.1415926) dePhi = dePhi - 2 * 3.1415926;
    if (dePhi < -3.1415926) dePhi = dePhi + 2 * 3.1415926;
    return dePhi;
}
 
double deltaR2(double eta1, double phi1, double eta2, double phi2) {
    double deta = eta1-eta2;
    double dphi = deltaPhi(phi1,phi2);
    return (deta*deta+dphi*dphi);
}

double deltaR(double eta1, double phi1, double eta2, double phi2) {
    double r2 = (deltaR2(eta1,phi1,eta2,phi2));
    return sqrt(r2);
}
