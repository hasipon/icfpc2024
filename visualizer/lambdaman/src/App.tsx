import {memo, useEffect, useState} from 'react'
import {Grid, Input, MenuItem, Select, Slider, TextField} from "@mui/material";
import axios from "axios";
import './App.css'

const SvgContent = memo((props: {field: string, solution: string, time: number}) => {
    let t = props.time;
    if (t < 0) {
        t = 0;
    }

    const stage = props.field.trim().split(/\r?\n/).map(line => line.split(""));
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

    for (let i = 0; i < Math.min(props.solution.trim().length, t); i++) {
        const c = props.solution[i];
        let nx = lx;
        let ny = ly;
        if (c === "L") nx--;
        if (c === "R") nx++;
        if (c === "U") ny--;
        if (c === "D") ny++;
        if (0 <= nx && nx < W && 0 <= ny && ny < H) {
            if (stage[ny][nx] === "#") {
                continue;
            }

            if (stage[ny][nx] === ".") {
                stage[ny][nx] = " ";
            }

            lx = nx;
            ly = ny;
        }
    }

    const svgChildren = [];
    const scale = 800 / Math.max(W, H);
    const pad = 0;

    svgChildren.push( <rect key={"rect_stage"} x={0} y={0} width={scale * W} height={scale * H} fillOpacity={1} fill={"black"}></rect> );

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

type Solution  = {
    fileName: string;
    size: number;
}

function App() {
    const [problemNo, setProblemNo] = useState<number>(1);
    const [solutionList, setSolutionList] = useState<Solution[]>([]);
    const [selectedSolution, setSelectedSolution] = useState<number>(0);
    const [inputText, setInputText] = useState<string>("###.#...\n" + "...L..##\n" + ".#######");
    const [movesText, setMovesText] = useState<string>("");
    const [outputText, setOutputText] = useState<string>("");
    const [time, setTime] = useState<number>(3);

    useEffect(() => {
        setTime(movesText.length);
    }, [movesText])

    useEffect(() => {
        const update = async () => {
            const resp = await axios.get<string>("http://34.146.140.6/repo/problems/lambdaman/" + problemNo + ".txt");
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
            const resp = await axios.get<string>("http://34.146.140.6/repo/solutions/lambdaman/");
            if (resp.status !== 200) {
                return;
            }

            const regex = /<a href="([^"]+)".* (\d+)/g;
            const matches = resp.data.matchAll(regex);
            const list :Solution[] = [{fileName: "None", size:0}];
            for (const match of matches) {
                if (match[1].startsWith(`${problemNo}-`) && match[1].endsWith(".icfp")) {
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
            const resp = await axios.get<string>("http://34.146.140.6/repo/solutions/lambdaman/" + s.fileName);
            if (resp.status !== 200) {
                return;
            }
            setOutputText(resp.data.trim());

            const resp2 = await axios.get<string>("http://34.146.140.6/repo/solutions/lambdaman/" + s.fileName.replace(".icfp", ".txt"), { responseType: "text" });
            if (resp2.status !== 200) {
                return;
            }
            setMovesText(resp2.data.trim());
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
                <Grid item xs={2}>
                    <TextField
                        sx={{display: "flex", margin:1}}
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
                <Grid item xs={10}>
                    <TextField
                        sx={{display: "flex", margin:1}}
                        variant="outlined"
                        label="ICFP"
                        multiline
                        rows="1"
                        onChange={(e) => {
                            setOutputText(e.target.value);
                        }}
                        value={outputText}
                    />
                    <TextField
                        sx={{display: "flex", margin:1}}
                        variant="outlined"
                        label="MOVES"
                        multiline
                        rows="1"
                        onChange={(e) => {
                            setMovesText(e.target.value);
                        }}
                        value={movesText}
                    />
                </Grid>
                <Grid item m={1} xs={6}>
                    <Slider
                        value={time}
                        max={movesText.length}
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
                            max: movesText.length,
                            type: 'number',
                            'aria-labelledby': 'input-slider',
                        }}
                    />
                </Grid>
                <Grid item xs={12}>
                    <SvgContent
                        field={inputText}
                        solution={movesText}
                        time={time}/>
                </Grid>
            </Grid>
        </>
    )
}

export default App
