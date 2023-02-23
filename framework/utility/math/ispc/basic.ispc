export void add_foreach(
    uniform const float in_a[], uniform const float in_b[], uniform float out[], uniform const size_t count){
        foreach(index = 0 ... count)
    {
        out[index] = in_a[index] + in_b[index];
    }
}
export void sub_foreach(
    uniform const float in_a[], uniform const float in_b[], uniform float out[], uniform const size_t count){
        foreach(index = 0 ... count)
    {
        out[index] = in_a[index] - in_b[index];
    }
}
export void mul_foreach(
    uniform const float in_a[], uniform const float in_b[], uniform float out[], uniform const size_t count){
        foreach(index = 0 ... count)
    {
        out[index] = in_a[index] * in_b[index];
    }
}
export void div_foreach(
    uniform const float in_a[], uniform const float in_b[], uniform float out[], uniform const size_t count){
            foreach(index = 0 ... count)
    {
        out[index] = in_a[index] / in_b[index];
    }
}