import {memo, useEffect, useState} from 'react'
import {Grid, Input, Slider, TextField} from "@mui/material";
import './App.css'

const SvgContent = memo((props: {field: string, solution: string, time: number}) => {
    let t = props.time;
    if (t < 0) {
        t = 0;
    }

    const stage = props.field.split(/\r?\n/).map(line => line.split(""));
    const H = stage.length;
    const W = 0 < H ? stage[0].length : 0;
    if (W <= 0 || H <= 0) {
        return;
    }

    let lx = 0, ly = 0;
    for (let y = 0; y < stage.length; y++) {
        for (let x = 0; x < stage[y].length; x++) {
            if (stage[y][x] === "L") {
                lx = x;
                ly = y;
                stage[y][x] = " ";
            }
        }
    }

    for (let i = 0; i < Math.min(props.solution.length, t); i++) {
        const c = props.solution[i];
        let nx = lx;
        let ny = ly;
        if (c === "L") nx--;
        if (c === "R") nx++;
        if (c === "U") ny--;
        if (c === "D") ny++;
        if (0 <= nx && nx < W && 0 <= ny && ny < H) {
            if (stage[ny][nx] === "#") {
                // TODO: print error
                break;
            }

            if (stage[ny][nx] === ".") {
                stage[ny][nx] = " ";
            }

            lx = nx;
            ly = ny;
        } else {
            // TODO: print error
            break;
        }
    }

    const svgChildren = [];
    const scale = 800 / Math.max(W, H);
    const pad = 0;

    svgChildren.push(
        <rect key={"rect_stage"} x={0} y={0} width={scale * W} height={scale * H} fillOpacity={1} strokeWidth={0} stroke={"#555555"}></rect>
    );

    for (let y = 0; y < stage.length; y++) {
        for (let x = 0; x < stage[y].length; x++) {
            const c = stage[y][x];
            const cx = x * scale + pad;
            const cy = y * scale + pad;
            if (c !== "#") {
                svgChildren.push(
                    <rect key={"rect_" + x + "_" + y} x={cx} y={cy} width={scale} height={scale} fill={"#444444"}></rect>
                );
            }

            if (c === ".") {
                svgChildren.push(
                    <circle key={"circle_" + x + "_" + y} cx={cx + scale / 2} cy={cy + scale / 2} r={scale * 0.2} fill={"#FFC800"}></circle>
                );
            }

            if (x === lx && y === ly) {
                svgChildren.push(
                    <circle key={"circle_" + x + "_" + y} cx={cx + scale / 2} cy={cy + scale / 2} r={scale * 0.4} fill={"#E00000"}></circle>
                );
            }
        }
    }

    return <svg width="800" height="800" viewBox="0 0 800 800" id="game">{svgChildren}</svg>
});

function App() {
    const [inputText, setInputText] = useState<string>("###.#...\n" + "...L..##\n" + ".#######");
    const [outputText, setOutputText] = useState<string>("LLL");
    const [time, setTime] = useState<number>(3);

    useEffect(() => {
        setTime(outputText.length);
    }, [outputText])

    return (
        <>
            <Grid container>
                <Grid item xs={6}>
                    <TextField
                        sx={{ display: "flex" }}
                        variant="outlined"
                        label="入力"
                        multiline
                        rows="4"
                        onChange={(e) => {
                            setInputText(e.target.value);
                        }}
                        value={inputText}
                    />
                </Grid>
                <Grid item xs={6}>
                    <TextField
                        sx={{ display: "flex" }}
                        variant="outlined"
                        label="出力"
                        multiline
                        rows="1"
                        onChange={(e) => {
                            setOutputText(e.target.value);
                        }}
                        value={outputText}
                    />
                </Grid>
                <Grid item m={1} xs={6}>
                    <Slider
                        value={time}
                        max={outputText.length}
                        onChange={(_e, newValue) => {
                            setTime(newValue as number);
                        }}
                        aria-labelledby="input-slider"
                    />
                </Grid>
                <Grid item m={1} xs={1}>
                    <Input
                        value={time}
                        onChange={e => {
                            setTime(parseInt(e.target.value));
                        }}
                        inputProps={{
                            step: 1,
                            min: 0,
                            max: outputText.length,
                            type: 'number',
                            'aria-labelledby': 'input-slider',
                        }}
                    />
                </Grid>
                <Grid item xs={12}>
                    <SvgContent
                        field={inputText}
                        solution={outputText}
                        time={time} />
                </Grid>
            </Grid>
        </>
    )
}

export default App
