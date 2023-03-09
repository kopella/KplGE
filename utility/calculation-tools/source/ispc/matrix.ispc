export void transpose(
    uniform const float mfin_a[], uniform float mfout[], uniform const size_t row_count, uniform const size_t col_count){
        foreach(i = 0 ... row_count, j = 0 ... col_count) {
		    mfout[j*row_count+i] = mfin_a[i*col_count+j];
	}
}

export void identity(uniform float data[], const uniform int n)
{
	foreach(i = 0 ... n, j = 0 ... n) {
		if (i == j)
			data[i * n + j] = 1;
		else
			data[i * n + j] = 0;
	}
}