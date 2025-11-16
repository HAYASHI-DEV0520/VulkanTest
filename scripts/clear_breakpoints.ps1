param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$File
)

# Visual Studio の DTE ProgID 候補
$progCandidates = @("VisualStudio.DTE.18.0","VisualStudio.DTE.17.0","VisualStudio.DTE.16.0")
$dte = $null
foreach ($p in $progCandidates) {
    try {
        $dte = [Runtime.InteropServices.Marshal]::GetActiveObject($p)
        break
    } catch { }
}

if (-not $dte) {
    Write-Error "Visual Studio の DTE に接続できません。Visual Studio を起動してから再実行してください。"
    exit 1
}

# ターゲットの正規化（可能ならフルパス）
try {
    $targetFull = (Get-Item -LiteralPath $File).FullName
} catch {
    # Resolve-Path でも失敗した場合はそのまま使う（部分一致で探す）
    $targetFull = $File
}

# ブレークポイントを逆順に走査して、ファイルが一致するものだけ削除
$bps = $dte.Debugger.Breakpoints
if ($bps.Count -eq 0) {
    Write-Host "現在ブレークポイントはありません。"
    exit 0
}

$removed = 0
for ($i = $bps.Count; $i -ge 1; $i--) {
    try {
        $bp = $bps.Item($i)
        $bpFile = $bp.File
        if ([string]::IsNullOrEmpty($bpFile)) {
            continue
        }

        # 比較用に可能ならフルパス化
        try {
            $bpFileFull = (Get-Item -LiteralPath $bpFile).FullName
        } catch {
            $bpFileFull = $bpFile
        }

        $match = $false
        if ($bpFileFull -and $targetFull) {
            if ($bpFileFull.ToLower() -eq $targetFull.ToLower()) {
                $match = $true
            } elseif ([System.IO.Path]::GetFileName($bpFileFull).ToLower() -eq [System.IO.Path]::GetFileName($targetFull).ToLower()) {
                # ファイル名のみ一致でも削除したい場合に備えて許容
                $match = $true
            }
        } else {
            if ($bpFile -like "*$File*") { $match = $true }
        }

        if ($match) {
            $bp.Delete()
            $removed++
        }
    } catch {
        Write-Warning "ブレークポイント処理中にエラー: $_"
    }
}

if ($removed -gt 0) {
    Write-Host "完了: $removed 個のブレークポイントを '$File' に対して削除しました。__Debug > Windows > Breakpoints__ で確認できます。"
} else {
    Write-Host "該当ファイルのブレークポイントは見つかりませんでした。"
}