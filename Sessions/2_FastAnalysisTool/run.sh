#!/bin/bash

root -l -b <<EOF
    .L AliLog.cxx+
    .L AliCheb3DCalc.cxx+
    .L AliCheb3D.cxx+
    .L AliMagWrapCheb.cxx+
    .L AliMagFast.cxx+
    .L AliMagF.cxx+

    .L AliVMisc.cxx+
    .L AliPDG.cxx++
    .L AliVVertex.cxx+
    .L AliPID.cxx+
    .L AliVParticle.cxx+
    .L AliVTrack.cxx+
    .L AliExternalTrackParam.cxx+

    .L DetectorK/HistoManager.cxx+
    .L DetectorK/DetectorK.cxx+
    .L lutWrite.cc
    .L lutWrite.detector.cc
    printLutWriterConfiguration();

    TDatabasePDG::Instance()->AddParticle("deuteron", "deuteron", 1.8756134, kTRUE, 0.0, 3, "Nucleus", 1000010020);
    TDatabasePDG::Instance()->AddAntiParticle("anti-deuteron", -1000010020);

    TDatabasePDG::Instance()->AddParticle("triton", "triton", 2.8089218, kTRUE, 0.0, 3, "Nucleus", 1000010030);
    TDatabasePDG::Instance()->AddAntiParticle("anti-triton", -1000010030);

    TDatabasePDG::Instance()->AddParticle("helium3", "helium3", 2.80839160743, kTRUE, 0.0, 6, "Nucleus", 1000020030);
    TDatabasePDG::Instance()->AddAntiParticle("anti-helium3", -1000020030);

    lutWrite_detector("lutCovm.el.5kG.20cm.dat", 11, 50, 20);

EOF
