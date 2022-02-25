matadd_src = ['matadd.cpp']
matmac_src = ['matmac.cpp']
matmul_src = ['matmul.cpp']
matfma_src = ['matfma.cpp']

matadd_exe = executable('matadd', matadd_src, include_directories : include_dir)
matmul_exe = executable('matmul', matmul_src, include_directories : include_dir)
matmac_exe = executable('matmac', matmac_src, include_directories : include_dir)
matfma_exe = executable('matfma', matfma_src, include_directories : include_dir)

test('matadd', matadd_exe)
test('matmul', matmul_exe)
test('matmac', matmac_exe)
test('matfma', matfma_exe)
