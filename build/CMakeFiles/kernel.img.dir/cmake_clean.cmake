file(REMOVE_RECURSE
  "kernel.img"
  "kernel.img.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang ASM C)
  include(CMakeFiles/kernel.img.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
