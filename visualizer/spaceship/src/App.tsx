import {memo, useEffect, useState} from 'react'
import {Grid, Input, MenuItem, Select, Slider, TextField} from "@mui/material";
import axios from "axios";
import './App.css'

const SvgContent = memo((props: {input: string, solution: string, time: number}) => {
    let t = props.time;
    if (t < 0) {
        t = 0;
    }

    if (!props.input) {
        return;
    }

    const stage = props.input.trim().split(/\r?\n/).map(line => line.split(" ").map(v => Number(v)));
    if (!stage) {
        return;
    }

    const targets = new Set();
    let min_x = -10, max_x = -10, min_y = 10, max_y = 10;
    for (let i = 0; i < stage.length; i++) {
        const x = stage[i][0];
        const y = stage[i][1];
        min_x = Math.min(min_x, x);
        max_x = Math.max(max_x, x);
        min_y = Math.min(min_y, y);
        max_y = Math.max(max_y, y);
        targets.add(`${x}_${y}`);
    }

    const W = max_x - min_x;
    const H = max_y - min_y;

    console.log(min_x, min_y, max_x, max_y);
    console.log(W, H);
    console.log(stage);

    if (W <= 0 || H <= 0) {
        return;
    }

    let px = 0, py = 0;
    let vx = 0, vy = 0;

    for (let i = 0; i < Math.min(props.solution.length, t); i++) {
        const c = props.solution[i];
        let ax = 0;
        let ay = 0;
        if (c === "1") { ax--; ay--; }
        if (c === "2") { ay--; }
        if (c === "3") { ax++; ay--; }
        if (c === "4") { ax--; }
        if (c === "6") { ax++}
        if (c === "7") { ax--; ay++; }
        if (c === "8") { ay++; }
        if (c === "9") { ax++; ay++; }

        vx += ax;
        vy += ay;
        px += vx;
        py += vy;
        targets.delete(`${px}_${py}`);

        if (vx == 0 && vy !== 0) {
            const num_p = Math.abs(vy);
            for (let dt = 0; dt < num_p; dt++) {
                const xx = px;
                const yy = py - vy * (dt + 1) / num_p;
                targets.delete(`${xx}_${yy}`);
            }
        } else if (vx !== 0 && vy == 0) {
            const num_p = Math.abs(vx);
            for (let dt = 0; dt < num_p; dt++) {
                const xx = px - vx * (dt + 1) / num_p;
                const yy = py;
                targets.delete(`${xx}_${yy}`);
            }
        } else if (vx !== 0 && vy !== 0) {
            const gcd = (x:number, y:number) => x % y ? gcd(y, x % y) : y;
            const num_p = gcd(Math.abs(vx), Math.abs(vy));
            for (let dt = 0; dt < num_p; dt++) {
                const xx = px - vx * (dt + 1) / num_p;
                const yy = py - vy * (dt + 1) / num_p;
                targets.delete(`${xx}_${yy}`);
            }
        }
    }

    const svgChildren = [];
    const r = 1 + Math.max(W,H) / 512;
    const flip_y = (y: number) => max_y - (y - min_y);

    svgChildren.push(
        <rect key={"rect_bg"} x={min_x} y={min_y} width={W+r} height={H+r} fill={"#CCCCCC"}></rect>
    );

    for (let i = 0; i < stage.length; i++) {
        const x = stage[i][0];
        const y = stage[i][1];
        if (targets.has(`${x}_${y}`)) {
            svgChildren.push(
                <rect key={"rect_" + i} x={x} y={flip_y(y)} width={r} height={r} fill={"#444444"}></rect>
            );
        }
    }

    console.log(px);
    svgChildren.push(
        <rect key={"rect_p"} x={px} y={flip_y(py)} width={r} height={r} fill={"#CC0000"}></rect>
    );

    return <svg width="1024" height="1024" viewBox={"" + (min_x) + " " + (min_y) + " " + (W+r) + " " + (H+r)} id="game">{svgChildren}</svg>
});

function App() {
    const [problemNo, setProblemNo] = useState<number>(1);
    const [solutionList, setSolutionList] = useState<string[]>([]);
    const [selectedSolution, setSelectedSolution] = useState<number>(0);
    const [inputText, setInputText] = useState<string>("");
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
