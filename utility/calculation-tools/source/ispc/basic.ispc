export void add_foreach(
    uniform const float vfin_a[], uniform const float vfin_b[], uniform float vfout[], uniform const size_t count){
        foreach(index = 0 ... count)
    {
        vfout[index] = vfin_a[index] + vfin_b[index];
    }
}
export void sub_foreach(
    uniform const float vfin_a[], uniform const float vfin_b[], uniform float vfout[], uniform const size_t count){
        foreach(index = 0 ... count)
    {
        vfout[index] = vfin_a[index] - vfin_b[index];
    }
}
export void mul_foreach(
    uniform const float vfin_a[], uniform const float vfin_b[], uniform float vfout[], uniform const size_t count){
        foreach(index = 0 ... count)
    {
        vfout[index] = vfin_a[index] * vfin_b[index];
    }
}
export void div_foreach(
    uniform const float vfin_a[], uniform const float vfin_b[], uniform float vfout[], uniform const size_t count){
            foreach(index = 0 ... count)
    {
        vfout[index] = vfin_a[index] / vfin_b[index];
    }
}
export void pow_foreach(
    uniform const float vfin_a[], uniform const float vfin_b[], uniform float vfout[], uniform const size_t count){
            foreach(index = 0 ... count)
    {
        vfout[index] = pow(vfin_a[index], vfin_b[index]);
    }
}
export void abs_foreach(
    uniform const float vfin[], uniform float vfout[], uniform const size_t count){
            foreach(index = 0 ... count)
    {
        vfout[index] = abs(vfin[index]);
    }
}
export void sqrt_foreach(
    uniform const float vfin[], uniform float vfout[], uniform const size_t count){
            foreach(index = 0 ... count)
    {
        vfout[index] = sqrt(vfin[index]);
    }
}
