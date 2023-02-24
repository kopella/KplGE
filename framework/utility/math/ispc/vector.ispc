export void cross(
    uniform const float vf3in_a[3], uniform const float v3fin_b[3], uniform float v3fout[3]){
	foreach(index = 0 ... 3) {
		int index_a = ((index + 1 == 3) ? 0 : index + 1);
		int index_b = ((index == 0) ? 2 : index - 1);
		v3fout[index] = vf3in_a[index_a] * v3fin_b[index_b] - vf3in_a[index_b] * v3fin_b[index_a];
	}
}