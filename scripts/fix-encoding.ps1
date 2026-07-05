# Convert all C++ source files to UTF-8 with BOM + CRLF line endings
# Run from repo root: pwsh -File scripts/fix-encoding.ps1

$sourceRoot = Join-Path $PSScriptRoot ".." "coding"
$extensions = @("*.h", "*.cpp")

foreach ($ext in $extensions) {
    $files = Get-ChildItem -LiteralPath $sourceRoot -Recurse -Include $ext
    foreach ($f in $files) {
        $content = Get-Content -LiteralPath $f.FullName -Raw -Encoding UTF8
        if (-not $content) { continue }

        # Normalize to CRLF (Windows)
        $content = $content -replace "`r`n", "`n" -replace "`n", "`r`n"

        $utf8Bom = New-Object System.Text.UTF8Encoding $true
        [System.IO.File]::WriteAllText($f.FullName, $content, $utf8Bom)
        Write-Host "UTF-8 BOM + CRLF: $($f.FullName)"
    }
}

Write-Host "Done."
