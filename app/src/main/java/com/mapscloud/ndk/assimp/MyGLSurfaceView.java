package com.mapscloud.ndk.assimp;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Environment;
import android.util.AttributeSet;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;

import androidx.core.view.GestureDetectorCompat;
import androidx.core.view.MotionEventCompat;

import com.mapscloud.libnativemate.assimp.AssimpMate;

import java.io.File;

/**
 * @author Tom灿
 * @description: 视图容器 需要扩展此类才能捕获触摸事件
 * @date :2023/8/18 15:17
 */
public class MyGLSurfaceView extends GLSurfaceView {

    private MyGLRenderer renderer;
    private String TAG = "MyGLSurfaceView";
    private GestureDetectorCompat mTapScrollDetector;
    private ScaleGestureDetector mScaleDetector;

    public MyGLSurfaceView(Context context) {
        this(context, null);
    }

    public MyGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
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

        renderer = new MyGLRenderer(context);

        // Set the Renderer for drawing on the GLSurfaceView
        setRenderer(renderer);
    }


    static {
        System.loadLibrary("AssimpMate");
    }


    static int INVALID_POINTER_ID = -100;
    private int mTwoFingerPointerId = INVALID_POINTER_ID;
    private float mLastTouchX, mLastTouchY;

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        // let the other detectors also consume the event
        mTapScrollDetector.onTouchEvent(event);
        mScaleDetector.onTouchEvent(event);
        Log.e(TAG, "onTouchEvent:" + event.getAction());
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN: {
                Log.e(TAG, "onTouchEvent: 按下");
                break;
            }
            case MotionEvent.ACTION_MOVE: {
                Log.e(TAG, "onTouchEvent: 移动");
                // track the drag only if two fingers are placed on screen
                if (mTwoFingerPointerId != INVALID_POINTER_ID) {

//                    final float x = MotionEventCompat.getX(event, mTwoFingerPointerId);
//                    final float y = MotionEventCompat.getY(event, mTwoFingerPointerId);
                    final float x = event.getX(mTwoFingerPointerId);
                    final float y = event.getY(mTwoFingerPointerId);
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
//                mTwoFingerPointerId = MotionEventCompat.getActionIndex(event);
                mTwoFingerPointerId = event.getActionIndex();
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
            Log.e(TAG, "onDoubleTap:滚动");
            if (mTwoFingerPointerId == INVALID_POINTER_ID) {
                AssimpMate.scrollAction(distanceX, distanceY, e2.getX(), e2.getY());
            }
            return true;
        }
    }

    // this class detects pinch and zoom gestures
    private class ScaleListener extends ScaleGestureDetector.SimpleOnScaleGestureListener {

        @Override
        public boolean onScale(ScaleGestureDetector detector) {
            Log.e(TAG, "onDoubleTap:缩放");
            AssimpMate.scaleAction(detector.getScaleFactor());
            return true;
        }
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
