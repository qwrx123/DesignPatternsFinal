#Windows clang-tidy wrapper


$FilteredArgs = @()
foreach ($arg in $args) {
    if ($arg -notmatch '-fmodules-ts' -and
        $arg -notmatch '-fdeps-format=.*' -and
        $arg -notmatch '-fmodule-mapper=.*') { #Do not match problematic flags
        $FilteredArgs += $arg
    }
}


& clang-tidy @FilteredArgs