package com.mapscloud.libnativemate.assimp;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import android.view.ViewGroup;

import com.mapscloud.libnativemate.R;

/**
 * @author Tom灿
 * @description:
 * @date :2024/2/22 14:17
 */
public class SceneView extends ViewGroup {

    private View operationView;
    private MyGLSurfaceView myGLSurfaceView;

    public SceneView(Context context) {
        super(context);
        myGLSurfaceView = new MyGLSurfaceView(context);
        operationView = inflate(context, R.layout.activity_main, null);
        addView(myGLSurfaceView);
    }

    public SceneView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public SceneView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public SceneView(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
        setMeasuredDimension(widthMeasureSpec, heightMeasureSpec);
        measureChildren(widthMeasureSpec, heightMeasureSpec);

    }

    @Override
    protected void onLayout(boolean c, int l, int t, int r, int b) {

    }
}
