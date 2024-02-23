package com.mapscloud.libnativemate.assimp;

import android.annotation.SuppressLint;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Environment;
import android.util.AttributeSet;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;

import androidx.annotation.NonNull;
import androidx.core.view.GestureDetectorCompat;
import androidx.core.view.MotionEventCompat;

import com.mapscloud.libnativemate.R;
import com.tomcan.android.gestures.AndroidGesturesManager;
import com.tomcan.android.gestures.RotateGestureDetector;
import com.tomcan.android.gestures.ShoveGestureDetector;

import java.io.File;

/**
 * @author Tom灿
 * @description: 视图容器 需要扩展此类才能捕获触摸事件
 * @date :2023/8/18 15:17
 */
public class MyGLSurfaceView extends GLSurfaceView implements ShoveGestureDetector.OnShoveGestureListener, RotateGestureDetector.OnRotateGestureListener {
    static {
        System.loadLibrary("AssimpMate");
    }

    private MyGLRenderer renderer;
    private String TAG = "MyGLSurfaceView";
    private GestureDetectorCompat mTapScrollDetector;
    private ScaleGestureDetector mScaleDetector;
    private AndroidGesturesManager androidGesturesManager;

    public MyGLSurfaceView(Context context) {
        this(context, null);
    }

    @SuppressLint("ResourceAsColor")
    public MyGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
//        setBackgroundColor(R.color.purple_700);
//        init(context);
        // Render the view only when there is a change in the drawing data 仅在绘图数据发生变化时才呈现视图
        //  To allow the triangle to rotate automatically, this line is commented out: 为了让三角形自动旋转，这一行被注释掉了(启动连续渲染):
//        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);

        // Create an OpenGL ES 2.0 context
        setEGLContextClientVersion(2);

        // instantiate two listeners for detecting double-tap/drag and pinch-zoom
        mTapScrollDetector = new GestureDetectorCompat(context, new MyTapScrollListener());
        mScaleDetector = new ScaleGestureDetector(context,
                new ScaleListener());

        androidGesturesManager = new AndroidGesturesManager(context);
        androidGesturesManager.setShoveGestureListener(this);
        androidGesturesManager.setRotateGestureListener(this);

        renderer = new MyGLRenderer(context);

        // Set the Renderer for drawing on the GLSurfaceView
        setRenderer(renderer);
    }


    static int INVALID_POINTER_ID = -100;
    private int mTwoFingerPointerId = INVALID_POINTER_ID;
    private float mLastTouchX, mLastTouchY;

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        Log.e(TAG, "onTouchEvent:" + event.toString());
        // let the other detectors also consume the event
        mTapScrollDetector.onTouchEvent(event);
        mScaleDetector.onTouchEvent(event);
        androidGesturesManager.onTouchEvent(event);
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN: {
                int index = event.getActionIndex();
                Log.e(TAG, "onTouchEvent: 按下:" + index);
                // detected two fingers, start the drag
                mTwoFingerPointerId = MotionEventCompat.getActionIndex(event);
                final float x = MotionEventCompat.getX(event, mTwoFingerPointerId);
                final float y = MotionEventCompat.getY(event, mTwoFingerPointerId);
                // Remember where we started (for dragging)
                mLastTouchX = x;
                mLastTouchY = y;
                break;
            }
            case MotionEvent.ACTION_MOVE: {
                int moveID = MotionEventCompat.getActionIndex(event);
                Log.e(TAG, "onTouchEvent: 移动:" + moveID);
                // track the drag only if two fingers are placed on screen
                if (mTwoFingerPointerId != INVALID_POINTER_ID) {
                    final float x = MotionEventCompat.getX(event, mTwoFingerPointerId);
                    final float y = MotionEventCompat.getY(event, mTwoFingerPointerId);

                    // Calculate the distance moved
                    final float dx = x - mLastTouchX;
                    final float dy = y - mLastTouchY;

                    // Remember this touch position for the next move event
                    mLastTouchX = x;
                    mLastTouchY = y;
                    AssimpMate.moveAction(dx, dy);
                }
                break;
            }

            case MotionEvent.ACTION_UP: {
                Log.e(TAG, "onTouchEvent: 抬起");
                mTwoFingerPointerId = INVALID_POINTER_ID;
                break;
            }

            case MotionEvent.ACTION_CANCEL: {
                Log.e(TAG, "onTouchEvent: 取消");
                mTwoFingerPointerId = INVALID_POINTER_ID;
                break;
            }

            case MotionEvent.ACTION_POINTER_DOWN: {
                Log.e(TAG, "onTouchEvent: 指示按下");
                // detected two fingers, start the drag
                mTwoFingerPointerId = MotionEventCompat.getActionIndex(event);
//                mTwoFingerPointerId = event.getActionIndex();
                final float x = MotionEventCompat.getX(event, mTwoFingerPointerId);
                final float y = MotionEventCompat.getY(event, mTwoFingerPointerId);

                // Remember where we started (for dragging)
                mLastTouchX = x;
                mLastTouchY = y;
                break;
            }

            case MotionEvent.ACTION_POINTER_UP: {
                Log.e(TAG, "onTouchEvent: 指示抬起");
                // two fingers are not placed on screen anymore
                mTwoFingerPointerId = INVALID_POINTER_ID;
                break;
            }
        }
        return true;
    }

    @Override
    public boolean onRotateBegin(@NonNull RotateGestureDetector rotateGestureDetector) {
        Log.e(TAG, "onRotateBegin: 旋转开始");
        return true;
    }

    @Override
    public boolean onRotate(@NonNull RotateGestureDetector rotateGestureDetector, float v, float v1) {
        Log.e(TAG, "onRotate: 旋转:" + v +"==="+v1);
        return true;
    }

    @Override
    public void onRotateEnd(@NonNull RotateGestureDetector rotateGestureDetector, float v, float v1, float v2) {
        Log.e(TAG, "onRotateEnd: 旋转结束");
    }


    // this class detects double-tap gesture and tracks the drag gesture by single finger
    class MyTapScrollListener extends GestureDetector.SimpleOnGestureListener {

        public boolean onDoubleTap(MotionEvent event) {
            Log.e(TAG, "onDoubleTap:双击");
            AssimpMate.doubleTapAction();
            return true;
        }

        // function is called if user scrolls with one/two fingers
        // we ignore the call if two fingers are placed on screen
        public boolean onScroll(MotionEvent e1, MotionEvent e2,
                                float distanceX, float distanceY) {
//            Log.e(TAG, "onScroll:滚动-->" + e1.toString() + "---" + e2.toString());
//            Log.e(TAG, "onScroll:滚动-->x=" + e2.getX()+"---y="+e2.getY());
//            Log.e(TAG, "onScroll:滚动-->distanceX=" + distanceX + "---distanceY=" + distanceY);
            int actionIndex = e1.getActionIndex();
            int actionIndex1 = e2.getActionIndex();
//            Log.e(TAG, "onScroll:滚动-->actionIndex=" + actionIndex+"---actionIndex2="+actionIndex1);
//            if (mTwoFingerPointerId == INVALID_POINTER_ID) {
//                AssimpMate.scrollAction(distanceX, distanceY, e2.getX(), e2.getY());
//            }
            return false;
        }
    }

    // this class detects pinch and zoom gestures
    private class ScaleListener extends ScaleGestureDetector.SimpleOnScaleGestureListener {

        @Override
        public boolean onScale(ScaleGestureDetector detector) {
            Log.e(TAG, "onScale:缩放");
            AssimpMate.scaleAction(detector.getScaleFactor());
            return true;
        }
    }


    @Override
    public boolean onShoveBegin(@NonNull ShoveGestureDetector shoveGestureDetector) {
        Log.e(TAG, "onShoveBegin:推压开始");
//        setRotationX(getRotationX() - shoveGestureDetector.getDeltaPixelsSinceStart());
//        MotionEvent currentEvent = shoveGestureDetector.getCurrentEvent();
//        MotionEvent previousEvent = shoveGestureDetector.getPreviousEvent();
//        AssimpMate.scrollAction(currentEvent.getX() - previousEvent.getX(),
//                currentEvent.getY() - previousEvent.getY(),
//                previousEvent.getX(), previousEvent.getY());
        return true;
    }

    @Override
    public boolean onShove(@NonNull ShoveGestureDetector shoveGestureDetector, float deltaPixelsSinceLast,
                           float deltaPixelsSinceStart) {
        Log.e(TAG, "onShove:推压:" + deltaPixelsSinceStart + "==="+ deltaPixelsSinceLast);
//        setRotationX(getRotationX() - deltaPixelsSinceLast);
        MotionEvent previousEvent = shoveGestureDetector.getPreviousEvent();
        MotionEvent currentEvent = shoveGestureDetector.getCurrentEvent();
        AssimpMate.scrollAction(currentEvent.getX() - previousEvent.getX(),
                currentEvent.getY() - previousEvent.getY(),
                currentEvent.getX(), currentEvent.getY());
        return true;
    }

    @Override
    public void onShoveEnd(@NonNull ShoveGestureDetector shoveGestureDetector, float v, float v1) {
        Log.e(TAG, "onShoveEnd:推压结束");
    }

    public void init(Context context) {
//        Utils.copyAssetAndWrite(context, "Man.JPG");
//        Utils.copyAssetAndWrite(context, "Man.mtl");
//        Utils.copyAssetAndWrite(context, "Man.obj");
//        File file = new File(context.getCacheDir(), "Man.obj");
//        Log.e(TAG, "文件路径: " + file.getPath());

        String rootPath =
                Environment.getExternalStorageDirectory().getAbsolutePath() + "/trans";
//        String modelObjPath = rootPath + "/navi3/model-merge";
        String modelObjPath = rootPath + "/data/obj";
        File file1 = new File(modelObjPath, "Man.obj");
        Log.e(TAG, "init: 模型文件路径：" + file1.getPath());
        Log.e(TAG, "init: 模型文件是否存在：" + file1.exists());
        AssimpMate.init(file1.getPath());
        AssimpMate.getAssetsFilePath(context.getAssets(), context.getFilesDir().getAbsolutePath());
    }


}
