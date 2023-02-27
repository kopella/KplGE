export void transpose(
    uniform const float mfin_a[], uniform float mfout[], uniform const size_t row_count, uniform const size_t col_count){
        foreach(i = 0 ... row_count, j = 0 ... col_count) {
		    mfout[j*row_count+i] = mfin_a[i*col_count+j];
	}
}