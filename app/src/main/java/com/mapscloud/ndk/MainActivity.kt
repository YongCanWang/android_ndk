package com.mapscloud.ndk

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.mapscloud.libnativemate.assimp.MyGLSurfaceView
import com.mapscloud.ndk.utils.PermissionsUtils

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        PermissionsUtils.getInstance(this) {
            setContentView(
                MyGLSurfaceView(
                    this
                )
            )
        }.checkSelfPermission()
    }
}