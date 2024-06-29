import {memo, useEffect, useState} from 'react'
import {Grid, Input, MenuItem, Select, Slider, TextField} from "@mui/material";
import axios from "axios";
import './App.css'

const SvgContent = memo((props: {input: string, solution: string, time: number}) => {
    let t = props.time;
    if (t < 0) {
        t = 0;
    }

    const stage = props.input.trim().split(/\r?\n/).map(line => line.split(" ").map(v => Number(v)));
    let min_x = -10, max_x = -10, min_y = 10, max_y = 10;
    for (let i = 0; i < stage.length; i++) {
        const x = stage[i][0];
        const y = stage[i][1];
        min_x = Math.min(min_x, x);
        max_x = Math.max(max_x, x);
        min_y = Math.min(min_y, y);
        max_y = Math.max(max_y, y);
    }

    const W = max_x - min_x;
    const H = max_y - min_y;

    console.log(W, H);
    console.log(stage);

    if (W <= 0 || H <= 0) {
        return;
    }

    // let px = 0, py = 0;
    /*
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
     */

    const svgChildren = [];
    const r = 1 + Math.max(W,H) / 512;

    svgChildren.push(
        <rect key={"rect_bg"} x={min_x} y={min_y} width={W+r} height={H+r} fill={"#CCCCCC"}></rect>
    );

    for (let i = 0; i < stage.length; i++) {
        const x = stage[i][0];
        const y = stage[i][1];
        const cx = x;
        const cy = y;
        svgChildren.push( <rect key={"rect_" + i} x={cx} y={cy} width={r} height={r} fill={"#444444"}></rect> );
    }

    return <svg width="1024" height="1024" viewBox={"" + (min_x) + " " + (min_y) + " " + (W+r) + " " + (H+r)} id="game">{svgChildren}</svg>
});

function App() {
    const [problemNo, setProblemNo] = useState<number>(1);
    const [solutionList, setSolutionList] = useState<string[]>([]);
    const [selectedSolution, setSelectedSolution] = useState<number>(0);
    const [inputText, setInputText] = useState<string>("###.#...\n" + "...L..##\n" + ".#######");
    const [outputText, setOutputText] = useState<string>("");
    const [time, setTime] = useState<number>(3);

    useEffect(() => {
        setTime(outputText.length);
    }, [outputText])

    useEffect(() => {
        const update = async () => {
            const resp = await axios.get<string>("http://34.146.140.6/repo/problems/spaceship/" + problemNo + ".txt");
            if (resp.status !== 200) {
                return;
            }

            // const regex = /<a href="([^"]+)"/g;
            setInputText(resp.data);
        };

        update();
    }, [problemNo]);

    useEffect(() => {
        const update = async () => {
            const resp = await axios.get<string>("http://34.146.140.6/repo/solutions/spaceship/");
            if (resp.status !== 200) {
                return;
            }

            const regex = /<a href="([^"]+)"/g;
            const matches = resp.data.matchAll(regex);
            const list = ["None"];
            for (const match of matches) {
                if (match[1].startsWith("" + problemNo + "-")) {
                    list.push(match[1]);
                }
            }

            setSolutionList(list);
        };

        update();
    }, [problemNo]);

    useEffect(() => {
        const update = async () => {
            if (selectedSolution === 0) {
                return;
            }

            if (solutionList.length <= selectedSolution) {
                return;
            }

            const s = solutionList[selectedSolution];
            const resp = await axios.get<string>("http://34.146.140.6/repo/solutions/lambdaman/" + s);
            if (resp.status !== 200) {
                return;
            }

            setOutputText(resp.data.trim());
        };

        update();
    }, [selectedSolution, solutionList]);

    return (
        <>
            <Grid container>
                <Grid item m={0} xs={6}>
                    <Input
                        type="number"
                        value={problemNo}
                        onChange={(e) => {
                            const v = Number(e.target.value);
                            if (1 <= v && v <= 21) {
                                setProblemNo(v);
                            }
                        }}
                    />
                </Grid>
                <Grid item m={0} xs={6}>
                    <Select
                        sx={{display: "flex"}}
                        value={selectedSolution}
                        onChange={(e) => {
                            const v = Number(e.target.value);
                            setSelectedSolution(v);
                        }}
                    >
                        {solutionList.map((s, index) => <MenuItem key={s} value={index}>{s}</MenuItem>)}
                    </Select>
                </Grid>
                <Grid item xs={6}>
                    <TextField
                        sx={{display: "flex"}}
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
                        sx={{display: "flex"}}
                        variant="outlined"
                        label="出力"
                        multiline
                        rows="4"
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
                        input={inputText}
                        solution={outputText}
                        time={time}/>
                </Grid>
            </Grid>
        </>
    )
}

export default App
