# Convert all C++ source files to UTF-8 with BOM
# Run from repo root: pwsh -File scripts/fix-encoding.ps1

$sourceRoot = Join-Path $PSScriptRoot ".." "coding"
$extensions = @("*.h", "*.cpp")

foreach ($ext in $extensions) {
    $files = Get-ChildItem -LiteralPath $sourceRoot -Recurse -Include $ext
    foreach ($f in $files) {
        $content = Get-Content -LiteralPath $f.FullName -Raw -Encoding UTF8
        if (-not $content) { continue }
        
        # Check if already BOM
        $bytes = [System.IO.File]::ReadAllBytes($f.FullName)
        $hasBom = ($bytes.Length -ge 3 -and $bytes[0] -eq 0xEF -and $bytes[1] -eq 0xBB -and $bytes[2] -eq 0xBF)
        
        if (-not $hasBom) {
            $utf8Bom = New-Object System.Text.UTF8Encoding $true
            [System.IO.File]::WriteAllText($f.FullName, $content, $utf8Bom)
            Write-Host "BOM added: $($f.FullName)"
        } else {
            Write-Host "OK (BOM): $($f.FullName)"
        }
    }
}

Write-Host "Done."
