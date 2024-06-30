import {memo, useEffect, useState} from 'react'
import {Grid, Input, MenuItem, Select, Slider, TextField} from "@mui/material";
import axios from "axios";
import './App.css'

const solutionToMoves = (solution: string) : string => {
    const pattern = /solve spaceship\d+/;
    return solution.replace(pattern, "").trim();
}

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

    const moves = solutionToMoves(props.solution);
    const targets = new Set();
    let min_x = -10, max_x = 10;
    let min_y = -10, max_y = 10;
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
    const get_a = (c: string) => {
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
        return [ax, ay];
    }

    for (let i = 0; i < Math.min(moves.length, t); i++) {
        const [ax, ay] = get_a(moves[i]);
        vx += ax;
        vy += ay;
        px += vx;
        py += vy;
        targets.delete(`${px}_${py}`);
    }

    const svgChildren = [];
    const r = 0.5 + Math.max(W,H) / 1024;
    const pad = 10;
    const flip_y = (y: number) => max_y - (y - min_y);

    svgChildren.push(
        <rect key={"rect_bg"} x={min_x-pad} y={min_y-pad} width={W+pad*2} height={H+pad*2} fill={"#CCCCCC"}></rect>
    );

    for (let i = 0; i < stage.length; i++) {
        const x = stage[i][0];
        const y = stage[i][1];
        svgChildren.push(
            <circle key={`stage_${i}`} cx={x} cy={flip_y(y)} r={r} fill={"#444444"} opacity={targets.has(`${x}_${y}`) ? 1 : 0}/>,
        );
    }

    svgChildren.push(
        <circle key={"player"} cx={px} cy={flip_y(py)} r={r} fill={"#CC0000"}/>
    );

    svgChildren.push(
        <line key={"line_v"} x1={px} y1={flip_y(py)} x2={px+vx} y2={flip_y(py+vy)} strokeWidth={r/2} stroke={"#CC0000"}></line>
    );

    const [ax, ay] = get_a(moves[t]);
    svgChildren.push(
        <line key={"line_a"} x1={px} y1={flip_y(py)} x2={px+ax} y2={flip_y(py+ay)} strokeWidth={r/2} stroke={"#0000CC"}></line>
    );

    return <>
        <pre>p={px},{py} v={vx},{vy} n={targets.size}</pre>
        <svg width="1024" height="1024" viewBox={`${min_x-pad} ${min_y-pad} ${W+pad*2} ${H+pad*2}`} id="game">{svgChildren}</svg>
    </>
});

type Solution = {
    fileName: string;
    size: number;
}

function App() {
    const [problemNo, setProblemNo] = useState<number>(1);
    const [solutionList, setSolutionList] = useState<Solution[]>([]);
    const [selectedSolution, setSelectedSolution] = useState<number>(0);
    const [inputText, setInputText] = useState<string>("");
    const [outputText, setOutputText] = useState<string>("");
    const [time, setTime] = useState<number>(3);

    useEffect(() => {
        setTime(solutionToMoves(outputText).length);
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

            const regex = /<a href="([^"]+)".* (\d+)/g;
            const matches = resp.data.matchAll(regex);
            const list :Solution[] = [{fileName: "None", size:0}];
            for (const match of matches) {
                if (match[1].startsWith("" + problemNo + "-")) {
                    list.push({fileName: match[1], size:Number(match[2])} as Solution);
                }
            }

            list.sort((a, b) => a.size - b.size);
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
            const resp = await axios.get<string>("http://34.146.140.6/repo/solutions/spaceship/" + s.fileName, {
                responseType: "text"
            });

            if (resp.status !== 200) {
                return;
            }

            if (resp.data) {
                console.log(resp.data);
                setOutputText(resp.data.trim());
            }
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
                        {solutionList.map((s, index) => <MenuItem key={s.fileName} value={index}>{"[" + s.size + "] " + s.fileName}</MenuItem>)}
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
                        max={solutionToMoves(outputText).length}
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
                            max: solutionToMoves(outputText).length,
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
