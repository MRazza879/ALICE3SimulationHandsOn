#!/bin/bash

rm AnalysisResults.root
# o2-analysis-alice3-tracking-performance --aod-file AO2D_converted.root -b


# o2-analysis-onthefly-tofpid -b --configuration json://configuration.json --aod-file AO2D_converted.root
o2-analysis-alice3-dilepton -b --configuration json://configuration.json --aod-file AO2D_converted.root
