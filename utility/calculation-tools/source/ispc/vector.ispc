export void cross(
    uniform const float vf3in_a[3], uniform const float v3fin_b[3], uniform float v3fout[3]){
	foreach(index = 0 ... 3) {
		int index_a = ((index + 1 == 3) ? 0 : index + 1);
		int index_b = ((index == 0) ? 2 : index - 1);
		v3fout[index] = vf3in_a[index_a] * v3fin_b[index_b] - vf3in_a[index_b] * v3fin_b[index_a];
	}
}

export void transform(uniform const float mfin[16], uniform float vf[4]){
    foreach(index = 0 ... 4) {
        vf[index] = (vf[0] * mfin[index*4]) 
            + (vf[1] * mfin[index*4 + 1]) 
            + (vf[2] * mfin[index*4 + 2]) 
            + (vf[3] * mfin[index*4 + 3]);
    }
}