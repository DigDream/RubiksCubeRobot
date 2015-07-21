package com.digdream.androidrubiksolver.ui;

import android.content.pm.ActivityInfo;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.ActionBarActivity;
import android.support.v7.widget.CardView;
import android.view.View;

import com.digdream.androidrubiksolver.R;
import com.digdream.androidrubiksolver.solver.Search;
import com.digdream.androidrubiksolver.solver.Tools;

import java.util.ArrayList;

/**
 * Created by user on 3/20/15.
 */
public class CustomActivity extends ActionBarActivity implements View.OnClickListener{
    //private final Color[] COLORS = { Color.white, Color.red, Color.green, Color.yellow, Color.orange, Color.blue };
    Search search = new Search();
    protected View[][] mColorPicker = new View[6][9];
    private int maxDepth = 21, maxTime = 5;
    boolean useSeparator = true;
    boolean showString = false;
    boolean inverse = true;
    boolean showLength = true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        setContentView(R.layout.activity_custom);

        findViewsById();
        CardView mCardView = (CardView)findViewById(R.id.cv_custom);
        mCardView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                solveCube();
            }
        });

        //randomCube();
    }

    private void findViewsById() {

    }

    protected Handler mMessageHandler = new Handler()
    {
        public void handleMessage(Message paramAnonymousMessage)
        {
            super.handleMessage(paramAnonymousMessage);
            //InputActivity.this.self.handleSolution(paramAnonymousMessage.getData());
        }
    };

    private void randomCube() {
        // +++++++++++++++++++++++++++++ Call Random function from package org.kociemba.twophase ++++++++++++++++++++
        String r = Tools.randomCube();
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 9; j++) {
                switch (r.charAt(9 * i + j)) {
                    case 'U':
                        mColorPicker[i][j].setBackgroundColor(R.color.rubik_color_white);
                        break;
                    case 'R':
                        mColorPicker[i][j].setBackgroundColor(R.color.rubik_color_red);
                        break;
                    case 'F':
                        mColorPicker[i][j].setBackgroundColor(R.color.rubik_color_green);
                        break;
                    case 'D':
                        mColorPicker[i][j].setBackgroundColor(R.color.rubik_color_yellow);
                        break;
                    case 'L':
                        mColorPicker[i][j].setBackgroundColor(R.color.rubik_color_orange);
                        break;
                    case 'B':
                        mColorPicker[i][j].setBackgroundColor(R.color.rubik_color_blue);
                        break;
                }
            }
    }

    private void solveCube() {
        //
        StringBuffer s = new StringBuffer(54);

        for (int i = 0; i < 54; i++)
            s.insert(i, 'B');// default initialization

        for (int i = 0; i < 6; i++)
            // read the 54 facelets
            for (int j = 0; j < 9; j++) {
                if (mColorPicker[i][j].getBackground() == mColorPicker[0][4].getBackground())
                    s.setCharAt(9 * i + j, 'U');
                if (mColorPicker[i][j].getBackground() == mColorPicker[1][4].getBackground())
                    s.setCharAt(9 * i + j, 'R');
                if (mColorPicker[i][j].getBackground() == mColorPicker[2][4].getBackground())
                    s.setCharAt(9 * i + j, 'F');
                if (mColorPicker[i][j].getBackground() == mColorPicker[3][4].getBackground())
                    s.setCharAt(9 * i + j, 'D');
                if (mColorPicker[i][j].getBackground() == mColorPicker[4][4].getBackground())
                    s.setCharAt(9 * i + j, 'L');
                if (mColorPicker[i][j].getBackground() == mColorPicker[5][4].getBackground())
                    s.setCharAt(9 * i + j, 'B');
            }
        String cubeString = s.toString();
        //if (showString) {
        //    JOptionPane.showMessageDialog(null, "Cube Definiton String: " + cubeString);
        //}
        int mask = 0;
        mask |= useSeparator ? Search.USE_SEPARATOR : 0;
        mask |= inverse ? Search.INVERSE_SOLUTION : 0;
        mask |= showLength ? Search.APPEND_LENGTH : 0;
        long t = System.nanoTime();
        String result = search.solution(cubeString, maxDepth, 100, 0, mask);;
        long n_probe = search.numberOfProbes();
        // ++++++++++++++++++++++++ Call Search.solution method from package org.kociemba.twophase ++++++++++++++++++++++++
        while (result.startsWith("Error 8") && ((System.nanoTime() - t) < maxTime * 1.0e9)) {
            result = search.next(100, 0, mask);
            n_probe += search.numberOfProbes();
        }
        t = System.nanoTime() - t;

        // +++++++++++++++++++ Replace the error messages with more meaningful ones in your language ++++++++++++++++++++++
        if (result.contains("Error"))
            switch (result.charAt(result.length() - 1)) {
                case '1':
                    result = "There are not exactly nine facelets of each color!";
                    break;
                case '2':
                    result = "Not all 12 edges exist exactly once!";
                    break;
                case '3':
                    result = "Flip error: One edge has to be flipped!";
                    break;
                case '4':
                    result = "Not all 8 corners exist exactly once!";
                    break;
                case '5':
                    result = "Twist error: One corner has to be twisted!";
                    break;
                case '6':
                    result = "Parity error: Two corners or two edges have to be exchanged!";
                    break;
                case '7':
                    result = "No solution exists for the given maximum move number!";
                    break;
                case '8':
                    result = "Timeout, no solution found within given maximum time!";
                    break;
            }
        //JOptionPane.showMessageDialog(null, result, Double.toString((t/1000)/1000.0) + " ms | " + n_probe + " probes", JOptionPane.INFORMATION_MESSAGE);
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    }


    @Override
    public void onClick(View v) {

    }
}
