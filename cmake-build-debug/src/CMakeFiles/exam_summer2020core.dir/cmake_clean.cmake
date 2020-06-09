file(REMOVE_RECURSE
  "../lib/libexam_summer2020core.a"
  "../lib/libexam_summer2020core.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/exam_summer2020core.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
