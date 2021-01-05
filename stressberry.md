# [stressberry](https://github.com/nschloe/stressberry)
There are a million ways to cool down your Raspberry Pi: Small heat sinks, specific cases, and some extreme DIY solutions. stressberry is a package for testing the core temperature under different loads, and it produces nice plots which can easily be compared.

### How to

To run stressberry on your computer, simply install it with
```
[sudo] apt install stress
pip install stressberry
```
and run it with
```
stressberry-run out.dat
stressberry-plot out.dat -o out.png
```
(Use `MPLBACKEND=Agg stressberry-plot out.dat -o out.png` if you're running the script
on the Raspberry Pi itself.)

The run lets the CPU idle for a bit, then stresses it with maximum load for 5 minutes,
and lets it cool down afterwards. The entire process takes 10 minutes.  The resulting
data is displayed to a screen or, if specified, written to a PNG file.

If you'd like to submit your own data for display here, feel free to [open an
issue](https://github.com/nschloe/stressberry/issues) and include the data file, a
photograph of your setup, and perhaps some further information.
